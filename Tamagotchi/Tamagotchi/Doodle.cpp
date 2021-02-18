#include "Doodle.h"
#include <cstdlib>
#include <random>

Doodle::Doodle()
{
}

Doodle::~Doodle()
{

}

void Doodle::Initialize(PlatformObject& Platform)
{
	Platform.Initialize();
	backgroundtexture.loadFromFile("Assets/Textures/background_02.png");
	background.setTexture(backgroundtexture);
	background.setScale(Vector2f(720.0f / backgroundtexture.getSize().x , 1040.0f / backgroundtexture.getSize().y));

	font.loadFromFile("Assets/Fonts/Minecraftia.ttf");
	scoreText.setFont(font);
	scoreText.setOutlineThickness(2.0f);
	scoreText.setCharacterSize(50);
	scoreText.setPosition(Vector2f(10.0f, 40.0f));
	scoreText.setFillColor(Color::Red);
	scoreText.setString("Score: " + std::to_string(score));

	buffer.loadFromFile("Assets/Sounds/apex_knockdown.wav");
	sound.setBuffer(buffer);
	/*buffer2.loadFromFile("Assets/Sounds/BlueberryFaygo.wav");
	music.setBuffer(buffer2);
	music.play();*/

}

void Doodle::Update(GravityObject& Alpha, PlatformObject& Platform, RenderWindow& window)
{
	if (gameover)
		return;
	if (Keyboard::isKeyPressed(Keyboard::A))
		Alpha.playerX -= 8;
	if (Keyboard::isKeyPressed(Keyboard::D))
		Alpha.playerX += 8;
	
	if (Alpha.playerX > 720)
		Alpha.playerX = 0;
	if (Alpha.playerX < 0)
		Alpha.playerX = 720;

	if (Alpha.playerY == Alpha.Height && Alpha.dy < -1.62f) {
		score += 1;
		//cout << score << "\n";
		scoreText.setString("Score: " + std::to_string(score));
		difficulty = score / 100;
	}

	Alpha.dy += 0.2f; 
	Alpha.playerY += Alpha.dy;
	
	if (Alpha.playerY < Alpha.Height) {
		for (unsigned int i = 0; i < Platform.NO_OF_PLATFORM; ++i) {
			Alpha.playerY = Alpha.Height;
			Platform.platformPos[i].y -= Alpha.dy;
			if (Platform.enabled[i] && Platform.platformPos[i].y > windowHeight) {
				Platform.platformPos[i].y = 0;
				Platform.platformPos[i].x = (rand() % (720 - 2 * (int)Platform.platform.GetSize().x)) + Platform.platform.GetSize().x;
			}
		}
	}

	for (unsigned int i = 0; i < Platform.NO_OF_PLATFORM; ++i) {
		if (Platform.enabled[i] && Alpha.CheckCollision(Platform.platformPos[i], Platform.platform.GetSize() / 2.0f) && Alpha.dy > 0.0f) {
			sound.play();
			Alpha.dy = 0;
			Alpha.dy -= 20.0f;
		}
	}

	if (Alpha.playerY > 1040)
	{
		scoreText.setPosition(230, 400);
		gameover = true;
	}

	Alpha.player.SetPosition(Vector2f(Alpha.playerX, Alpha.playerY));
}

void Doodle::Draw(GravityObject &Alpha , PlatformObject& Platform , RenderWindow& window)
{
	if (gameover) {
		window.draw(scoreText);
	}
	else {
		window.draw(background);
		Platform.Draw(window, difficulty);
		Alpha.player.Draw(window);
		window.draw(scoreText);
	}
	
}
