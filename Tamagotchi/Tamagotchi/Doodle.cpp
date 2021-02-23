#include "Doodle.h"
#include <cstdlib>
#include <random>

Doodle::Doodle()
{

}

Doodle::~Doodle()
{

}

void Doodle::Initialize()
{

	static PlatformObject p = PlatformObject(Vector2f(100.0f, 20.0f), Vector2i(windowWidth, windowHeight), 7 , "Assets/Textures/platform2.png");
	Platform = &p;

	static GravityObject a = GravityObject(Vector2f(520.0f, 400.0f), Vector2f(80.0f, 115.0f), 400.0f, "Assets/Textures/doodlenew2.png");
	Alpha = &a;

	int r =  rand() % 5 + 1;
	backgroundtexture.loadFromFile("Assets/Textures/background_0" + std::to_string(r) + ".png");
	background.setTexture(backgroundtexture);
	background.setScale(Vector2f(720.0f / backgroundtexture.getSize().x , 1040.0f / backgroundtexture.getSize().y));

	Logo1T.loadFromFile("Assets/Textures/DoodleLogo1.png");
	Logo2T.loadFromFile("Assets/Textures/DoodleLogo2.png");
	Logo1.setPosition(Vector2f(-720.0f, 120.0f));
	Logo2.setPosition(Vector2f(920.0f, 250.0f));
	Logo1.setTexture(Logo1T);
	Logo2.setTexture(Logo2T);
	Logo1.setScale(Vector2f(10.0f,10.0f));
	Logo2.setScale(Vector2f(10.0f, 10.0f));

	PressT.loadFromFile("Assets/Textures/PressAnyKeyToStartGame.png");
	Press.setTexture(PressT);
	Press.setScale(Vector2f(10.0f, 10.0f));
	Press.setOrigin(Vector2f(PressT.getSize().x / 2.0f, PressT.getSize().y / 2.0f));
	//Press.setColor(Color::Green);
	Press.setPosition(Vector2f(360.0f, 800.0f));
	

	font.loadFromFile("Assets/Fonts/Minecraftia.ttf");
	scoreText.setFont(font);
	scoreText.setOutlineThickness(3.0f);
	scoreText.setOutlineColor(Color::White);
	scoreText.setCharacterSize(50);
	scoreText.setPosition(Vector2f(10.0f, 40.0f));
	scoreText.setFillColor(Color::Red);
	scoreText.setString("Score: " + std::to_string(score));

	buffer.loadFromFile("Assets/Sounds/Shot.wav");
	sound.setBuffer(buffer);
	buffer2.loadFromFile("Assets/Sounds/DoodleBG.wav");
	music.setBuffer(buffer2);
	music.setLoop(true);

}

void Doodle::Update(float deltaTime)
{
	if (gamestate == 0) {
		if(Logo1.getPosition().x < 60.0f)
			Logo1.move(Vector2f(600.0f * deltaTime, 0.0f));
		if (Logo2.getPosition().x > 90.0f)
			Logo2.move(Vector2f(-600.0f * deltaTime, 0.0f));
		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			music.play();
			gamestate = 1;
		}
	}
	else if (gamestate == 1) {
		if (Keyboard::isKeyPressed(Keyboard::A))
			Alpha->playerX -= 800.0f * deltaTime * (1.0f - ((float)(difficulty) / (float)Platform->NO_OF_PLATFORM * 0.75f));
		if (Keyboard::isKeyPressed(Keyboard::D))
			Alpha->playerX += 800.0f * deltaTime * (1.0f - ((float)(difficulty) / (float)Platform->NO_OF_PLATFORM * 0.75f));
		if (Alpha->playerX > 720)
			Alpha->playerX = 0;
		if (Alpha->playerX < 0)
			Alpha->playerX = 720;
		
		if (Alpha->playerY == Alpha->Height && Alpha->dy < -162.0f) {
			score += 1;
			scoreText.setString("Score: " + std::to_string(score / 500));
			difficulty = score / 500 / 60;
		}

		Alpha->dy += 0.4f;
		Alpha->playerY += Alpha->dy * deltaTime;

		if (Alpha->playerY < Alpha->Height) {
			for (unsigned int i = 0; i < Platform->NO_OF_PLATFORM; ++i) {
				Alpha->playerY = Alpha->Height;
				Platform->platformPos[i].y -= Alpha->dy * deltaTime;
				if (Platform->enabled[i] && Platform->platformPos[i].y > windowHeight) {
					Platform->platformPos[i].y = 0;
					Platform->platformPos[i].x = (rand() % (720 - 2 * (int)Platform->platform.GetSize().x)) + Platform->platform.GetSize().x;
				}
			}
		}

		for (unsigned int i = 0; i < Platform->NO_OF_PLATFORM; ++i) {
			if (!(!Platform->enabled[i] && Platform->platformPos[i].y > windowHeight) && Alpha->CheckCollision(Platform->platformPos[i], Platform->platform.GetSize() / 2.0f) && Alpha->dy > 0.0f) {
				sound.play();
				Alpha->dy = 0.0f;
				Alpha->dy -= 1500.0f;
				
			}
		}

		if (Alpha->playerY > 1040)
		{
			FloatRect bound = scoreText.getLocalBounds();
			scoreText.setOrigin(Vector2f(bound.left + bound.width / 2.0f, bound.top + bound.height / 2.0f));
			scoreText.setPosition(360, 400);
			gamestate = 2;
		}
		
		Alpha->player.SetPosition(Vector2f(Alpha->playerX, Alpha->playerY));
	}
}

void Doodle::Draw(RenderWindow& window)
{
	window.draw(background);
	if (gamestate == 0) {
		window.draw(Logo1);
		window.draw(Logo2);
		window.draw(Press);
	}
	if (gamestate == 1) {
		if (difficulty > Platform->NO_OF_PLATFORM)
			difficulty = Platform->NO_OF_PLATFORM - 1;
		Platform->Draw(window, difficulty);
		Alpha->player.Draw(window);
		window.draw(scoreText);
	}
	if (gamestate == 2) {
		window.draw(scoreText);
	}
		
		
}
