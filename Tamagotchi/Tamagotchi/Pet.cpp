#include "Pet.h"

Pet::Pet() : GameObject()
{
}

Pet::Pet(Vector2f position, Vector2f dimensions, bool originIsCenter,//Proper Animation
	string texturePath, Vector2u imageCount, Vector2i start, Vector2i finish, float frameTime)
	: GameObject(position, dimensions, originIsCenter, texturePath, imageCount, start, finish, frameTime)
{
}

Pet::Pet(Vector2f position, Vector2f dimensions, bool originIsCenter,//Customize Pet
	string texturePath, Vector2u imageCount, Vector2i start, Vector2i finish, float frameTime,
	string name, string type, int levelMax, vector<int> hpMax, vector<int> expPerEvolve, vector<int> happinessMax, vector<int> foodMax, vector<int> poopMax,
	int hpChangeRate, int expChangeRate, int foodChangeRate, int happinessChangeRate, int poopChangeRate, float notEnoughFoodThreshold)
	: GameObject(position, dimensions, originIsCenter, texturePath, imageCount, start, finish, frameTime)
{
	this->name = name;
	this->type = type;
	this->levelMax = levelMax;
	currentLevel = 1;
	this->hpMax = hpMax;
	currentHp = this->hpMax[0];
	this->expPerEvolve = expPerEvolve;
	currentExp = expPerEvolve[0];
	this->happinessMax = happinessMax;
	currentHappiness = this->happinessMax[0];
	this->foodMax = foodMax;
	currentFood = this->foodMax[0];
	this->poopMax = poopMax;
	currentPoop = 0;
	this->hpChangeRate = hpChangeRate;
	this->expChangeRate = expChangeRate;
	this->foodChangeRate = foodChangeRate;
	this->happinessChangeRate = happinessChangeRate;
	this->poopChangeRate = poopChangeRate;
	this->notEnoughFoodThreshold = notEnoughFoodThreshold;
}

Pet::Pet(Vector2f position, Vector2f dimensions, bool originIsCenter,//By Type
	string texturePath, Vector2u imageCount, Vector2i start, Vector2i finish, float frameTime,
	string name, string type) : GameObject(position, dimensions, originIsCenter, texturePath, imageCount, start, finish, frameTime)
{
	if (type == "Type1") {
		//Set stuff
	}
	else if (type == "Type2") {
		//Set more stuff
	}

}

Pet::~Pet()
{
}






