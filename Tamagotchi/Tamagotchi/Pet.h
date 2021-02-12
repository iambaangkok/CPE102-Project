#pragma once
#include <iostream>
#include <chrono>
#include <ctime>  
#include <vector>
#include "GameObject.h"

using std::vector;

class Pet :
    public GameObject
{
public:
	Pet();
	Pet(Vector2f position, Vector2f dimensions, bool originIsCenter,//Proper Animation
		string texturePath, Vector2u imageCount, Vector2i start, Vector2i finish, float frameTime);
	Pet(Vector2f position, Vector2f dimensions, bool originIsCenter,//Customize Pet
		string texturePath, Vector2u imageCount, Vector2i start, Vector2i finish, float frameTime,
		string name, string type, int levelMax, vector<int> hpMax, vector<int> expPerEvolve, vector<int> happinessMax, vector<int> foodMax, vector<int> poopMax,
		int hpChangeRate = 1, int expChangeRate = 1, int foodChangeRate = 1, int happinessChangeRate = 1, int poopChangeRate = 1, float notEnoughFoodThreshold = 20);
	Pet(Vector2f position, Vector2f dimensions, bool originIsCenter,//By Type
		string texturePath, Vector2u imageCount, Vector2i start, Vector2i finish, float frameTime, 
		string name, string type);
	~Pet();


	string name;
	string type;
	int currentLevel;
	int currentHp;
	int currentExp;
	int currentHappiness;
	int currentFood;
	int currentPoop;

	float hpChangeRateMultiplier = 1.0f;
	float expChangeMultiplier = 1.0f;
	float foodChangeMultiplier = 1.0f;
	float happinessChangeMultiplier = 1.0f;
	float poopChangeMultiplier = 1.0f;


private:
	int levelMax;
	vector<int> hpMax; //HP
	vector<int> expPerEvolve; //EXP
	vector<int> happinessMax; //Happiness
	vector<int> foodMax; //Food
	vector<int> poopMax; //Poop

	//All Rate are at 1 per X minute;
	int hpChangeRate = 1;
	int expChangeRate = 1;
	int foodChangeRate = 1;
	int happinessChangeRate = 1;
	int poopChangeRate = 1;

	float notEnoughFoodThreshold = 20; //If Food is below this PERCENT, HP starts to decay

};

