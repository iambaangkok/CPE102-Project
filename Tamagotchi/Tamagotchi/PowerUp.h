#pragma once
#include "GameObject.h"

class PowerUp
{
public :
	PowerUp();
	~PowerUp();

	void Update(float deltaTime);
	void Draw(RenderWindow& window);
	bool CheckCollision(Vector2f otherPos, Vector2f otherHalfSize);

	GameObject POWERUP; 
	Texture POWERUPT;

	int posx;
	

	bool spawn = false;
	int state = 0;
	int prev = 0;
};

