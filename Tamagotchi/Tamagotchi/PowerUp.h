#pragma once
#include "GameObject.h"

class PowerUp
{
public :
	PowerUp(string filepath , Vector2f size);
	~PowerUp();

	void Update(float deltaTime);
	void Draw(RenderWindow& window);
	bool CheckCollision(Vector2f otherPos, Vector2f otherHalfSize);

	GameObject POWERUP; 
	Texture POWERUPT;

	int posx;
	
	int state = 0;
	int prev = 0;
};

