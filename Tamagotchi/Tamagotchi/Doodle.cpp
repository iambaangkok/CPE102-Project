#include "Doodle.h"
#include <cstdlib>
#include <random>

Doodle::Doodle(int& maingame_state)
{
	this->maingame_state = &maingame_state;
	static PlatformObject p = PlatformObject(Vector2f(100.0f, 20.0f), Vector2i(windowWidth, windowHeight), 9, "Assets/Textures/platform2.png");
	Platform = &p;
	static GravityObject a = GravityObject(Vector2f(360.0f, 575.0f), Vector2f(100.0f, 100.0f), 400.0f, "Assets/Textures/pet_01.png");
	Alpha = &a;
	static PowerUp power = PowerUp();
	Power = &power;
	static GameObject l = GameObject(Vector2f(360, 800), Vector2f(720, 480), true, "Assets/Textures/background_land.png");
	land = &l;
	
	int r = rand() % 4 + 1;
	for (int i = 0; i < 2; ++i)
	{
		Sprite A;
		//backgroundT.loadFromFile("Assets/Textures/bgex" + std::to_string(r) + ".png");
		backgroundT.loadFromFile("Assets/Textures/bgex4.png");
		A.setTexture(backgroundT);
		A.setScale(Vector2f(720.0f / backgroundT.getSize().x, 1040.0f / backgroundT.getSize().y));
		background.push_back(A);
	}

	Logo1T.loadFromFile("Assets/Textures/DoodleLogo1.png");
	Logo2T.loadFromFile("Assets/Textures/DoodleLogo2.png");
	Logo1.setTexture(Logo1T);
	Logo2.setTexture(Logo2T);

	PressT.loadFromFile("Assets/Textures/PressAnyKeyToStartGame.png");
	Press.setTexture(PressT);
	Press.setScale(Vector2f(10.0f, 10.0f));
	Press.setOrigin(Vector2f(PressT.getSize().x / 2.0f, PressT.getSize().y / 2.0f));

	font.loadFromFile("Assets/Fonts/Minecraftia.ttf");
	scoreText.setFont(font);
	scoreText.setOutlineThickness(3.0f);
	scoreText.setOutlineColor(Color::White);
	scoreText.setCharacterSize(50);
	scoreText.setFillColor(Color::Red);
	scoreText.setString("Score: " + std::to_string(score));

	YOUDIEDT.loadFromFile("Assets/Textures/GAMEOVER.png");
	YOUDIED.setTexture(YOUDIEDT);
	YOUDIED.setScale(Vector2f(10.0f, 10.0f));
	FloatRect bound1 = YOUDIED.getLocalBounds();
	YOUDIED.setOrigin(Vector2f(bound1.left + bound1.width / 2.0f, bound1.top + bound1.height / 2.0f));

	soundB.loadFromFile("Assets/Sounds/Jump.wav");
	sound.setBuffer(soundB);
	musicB.loadFromFile("Assets/Sounds/DoodleBG.wav");
	music.setBuffer(musicB);
	pwB.loadFromFile("Assets/Sounds/PowerUp.wav");
	pw.setBuffer(pwB);
	music.setLoop(true);
	music.setVolume(15.0f);
	sound.setVolume(15.0f);
}

Doodle::~Doodle()
{
}

void Doodle::Initialize()
{
	
	Alpha->player.animation.SetFrame(Vector2i(0, 0));
	Alpha->dy = 0;
	Alpha->dy -= 1700.0f;
	Alpha->player.SetPosition(Vector2f(360.0f, 575.0f));
	Alpha->playerX = 360.0f;
	Alpha->playerY = 575.0f;

	//cout << Alpha->player.GetPosition().x << " " << Alpha->player.GetPosition().y << endl; 
	Platform->Initialize();

	Power->state = 0;

	land_posy = 800.0f;
	land->SetPosition(Vector2f(360, land_posy));

	background[0].setPosition(Vector2f(0, -1040));
	background[1].setPosition(Vector2f(0, 0));
	
	Logo1.setPosition(Vector2f(-720.0f, 120.0f));
	Logo2.setPosition(Vector2f(920.0f, 250.0f));
	
	Logo1.setScale(Vector2f(10.0f, 10.0f));
	Logo2.setScale(Vector2f(10.0f, 10.0f));

	Press.setPosition(Vector2f(360.0f, 800.0f));

	scoreText.setPosition(Vector2f(30.0f, 60.0f));

	YOUDIED.setPosition(Vector2f(360, 400));
	YOUDIED.setColor(Color::Color(255, 255, 255, 0));
	
	beta = rand() % power_range + 1;

}

void Doodle::Update(float deltaTime)
{
	if (*maingame_state == 2 && !callgame) {
		Initialize();
		gstate = 0;
		callgame = true;
	}
	else if (gstate == 0)
	{
		if (Logo1.getPosition().x < 60.0f)
			Logo1.move(Vector2f(600.0f * deltaTime, 0.0f));
		if (Logo2.getPosition().x > 90.0f)
			Logo2.move(Vector2f(-650.0f * deltaTime, 0.0f));
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			music.play();
			sound.play();
			gstate = 1;
		}
	}
	else if (gstate == 1)
	{

		if (Alpha->playerY == Alpha->Height && Alpha->dy < -162.0f)
		{
			score += 1;
			scoreText.setString("Score: " + std::to_string(score / score_rate));
			difficulty = score / score_rate / difficulty_rate;
			if (difficulty > Platform->NO_OF_PLATFORM - 1)
				difficulty = Platform->NO_OF_PLATFORM - 1;
			
			if ((score / score_rate) != 0 && ((score / score_rate) + beta) % power_range == 0 && !Power->spawn) {
				Power->state = 1;
				Power->spawn = true;
			}
		}

		Alpha->dy += 20.0f;
		Alpha->playerY += Alpha->dy * deltaTime;

		if (Alpha->playerY < Alpha->Height)
		{
			for (unsigned int i = 0; i < Platform->NO_OF_PLATFORM; ++i)
			{
				Alpha->playerY = Alpha->Height;
				Platform->platformPos[i].y -= Alpha->dy * deltaTime * 0.9f;
				land_posy -= Alpha->dy * deltaTime * 0.15f ;
				if (Platform->enabled[i] && Platform->platformPos[i].y > windowHeight)
				{
					Platform->platformPos[i].y = 0;
					Platform->platformPos[i].x = (rand() % (720 - 2 * (int)Platform->platform.GetSize().x)) + Platform->platform.GetSize().x;
				}
			}
			for (unsigned int i = 0; i < 2; ++i)
			{
				background[i].move(Vector2f(0, - Alpha->dy * deltaTime * 0.02f));
				if (background[i].getPosition().y > windowHeight)
					background[i].setPosition(Vector2f(0, -1040));
			}
		}

		for (unsigned int i = 0; i < Platform->NO_OF_PLATFORM; ++i)
		{
			if (!(!Platform->enabled[i] && Platform->platformPos[i].y > windowHeight) && Alpha->CheckCollision(Platform->platformPos[i], Platform->platform.GetSize() / 2.0f) && Alpha->dy > 0.0f)
			{
				sound.play();
				Alpha->dy = 0.0f;
				Alpha->dy -= 1700.0f;
			}
		}

		if (Power->CheckCollision(Alpha->player.GetPosition(), Alpha->player.GetSize() / 2.0f)) {
			pw.play();
			Power->spawn = false;
			Power->state = 0;
			Alpha->dy = 0.0f;
			Alpha->dy -= 4000.0f;
		}

		if (Alpha->playerY > 1040)
		{
			FloatRect bound = scoreText.getLocalBounds();
			scoreText.setOrigin(Vector2f(bound.left + bound.width / 2.0f, bound.top + bound.height / 2.0f));
			scoreText.setPosition(-360, 800);
			gstate = 2;
		}
		float speed = (float)difficulty / (float)Platform->NO_OF_PLATFORM;
		Alpha->Update(deltaTime, (speed * (1 - finalspeed_rate)));
		Power->Update(deltaTime);
		land->SetPosition(360 , land_posy);
	}
	else if (gstate == 2)
	{
		if (scoreText.getPosition().x < 360.0f)
			scoreText.move(Vector2f(500.0f, 0.0f) * deltaTime);
		if (FadeCnt < 255.0f / FadeRate)
		{
			YOUDIED.setColor(Color::Color(255, 255, 255, FadeCnt * FadeRate));
			FadeCnt++;
		}
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			music.stop();
			callgame = false;
			*maingame_state = 1;
		}
	}
}

void Doodle::Draw(RenderWindow &window)
{
	if (*maingame_state != 2)
		return;
	window.draw(background[0]);
	window.draw(background[1]);
	land->Draw(window);
	
	if (gstate == 0)
	{
		window.draw(Press);
		window.draw(Logo1);
		window.draw(Logo2);
		
		Alpha->player.Draw(window);
	}
	if (gstate == 1)
	{
		Platform->Draw(window, difficulty);
		window.draw(scoreText);
		Power->Draw(window);
		Alpha->player.Draw(window);
	}
	if (gstate == 2)
	{
		window.clear(Color::White);
		window.draw(YOUDIED);
		window.draw(scoreText);
	}

}
