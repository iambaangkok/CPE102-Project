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
}

void Doodle::Update(GravityObject& Alpha, PlatformObject& Platform, RenderWindow& window)
{
	if (Keyboard::isKeyPressed(Keyboard::A))
		Alpha.playerX -= 4;
	if (Keyboard::isKeyPressed(Keyboard::D))
		Alpha.playerX += 4;
	
	if (Alpha.playerX > 720)
		Alpha.playerX = 0;
	if (Alpha.playerX < 0)
		Alpha.playerX = 720;

	if (Alpha.playerY == Alpha.Height && Alpha.dy < -1.62f) {
		score += 1;
	}

	Alpha.dy += 0.2f; 
	Alpha.playerY += Alpha.dy;
	
	if (Alpha.playerY < Alpha.Height) {
		for (unsigned int i = 0; i < Platform.NO_OF_PLATFORM; ++i) {
			Alpha.playerY = Alpha.Height;
			Platform.platformPos[i].y -= Alpha.dy;
			if (Platform.platformPos[i].y > windowHeight) {
				Platform.platformPos[i].y = 0;
				Platform.platformPos[i].x = (rand() % (720 - 2 * (int)Platform.platform.GetSize().x)) + Platform.platform.GetSize().x;
			}
		}
	}

	for (unsigned int i = 0; i < Platform.NO_OF_PLATFORM; ++i) {
		if (Alpha.CheckCollision(Platform.platformPos[i], Platform.platform.GetSize() / 2.0f) && Alpha.dy > 0.0f) {
			Alpha.dy -= 25.0f;
		}
	}
	cout << Alpha.dy << "\n";
	cout << Alpha.playerX << " " << Alpha.playerY << "\n";
	Alpha.player.SetPosition(Vector2f(Alpha.playerX, Alpha.playerY));
}

void Doodle::Draw(GravityObject &Alpha , PlatformObject& Platform , RenderWindow& window)
{
	Alpha.player.Draw(window);
	Platform.Draw(window);
}
