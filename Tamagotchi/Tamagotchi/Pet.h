#pragma once
#include "GameObject.h"
class Pet :
    public GameObject
{
public:
	Pet();
	Pet(Vector2f position, Vector2f dimensions, bool originIsCenter,
		string texturePath, Vector2u imageCount, Vector2i start, Vector2i finish, float frameTime); //Proper Animation
	~Pet();

	string name;
	int levelMax, currentLevel;
	int hpMax, currentHp;
	int expMax, currentExp;
	int happinessMax, currentHappiness;
	int foodMax, currentFood;
	int poopMax, currentPoop;

};

