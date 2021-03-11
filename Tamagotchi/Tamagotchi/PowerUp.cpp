#include "PowerUp.h"

PowerUp::PowerUp()
{
	POWERUP.SetDimensions(19.0f * 2, 34.0f * 2);
	POWERUPT.loadFromFile("Assets/Textures/PowerUp.png");
	POWERUP.rectangleShape.setTexture(&POWERUPT , true);
}

PowerUp::~PowerUp()
{
}

void PowerUp::Update(float deltaTime)
{
	if (state != prev) {
		prev = state;
	}
		
	switch (state) {
	case 0 :
		POWERUP.SetPosition(0.0f,-100.0f);
		break;
	case 1 :
		posx = rand() % 520 + 100;
		POWERUP.SetPosition(posx, -100.0f);
		state = 2;
		break;
	case 2 :
		POWERUP.Move(0.0f, 250.0f * deltaTime);
		break;
	default :
		break;
	}
}

void PowerUp::Draw(RenderWindow &window)
{
	POWERUP.Draw(window);
}

bool PowerUp::CheckCollision(Vector2f otherPos, Vector2f otherHalfSize)
{
	Vector2f thisPos = POWERUP.GetPosition();
	Vector2f thisHalfSize = POWERUP.GetSize() / 2.0f;

	float deltaX = otherPos.x - thisPos.x;
	float deltaY = otherPos.y - thisPos.y;

	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if (intersectX < 0.0f && intersectY < 0.0f) {
		return true;
	}
	return false;
}
