#pragma once
#include <iostream>
#include <chrono>
#include <ctime>  
#include <vector>
#include "GameObject.h"
#include "Item.h"
using std::vector;
class Item;

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


	void Initialize();//Runs before everything else in every game loop/ reset variable that needs to be reset every game loop

	void Update(float deltaTime);

	template <typename T>
	void Clamp(T* clampVariable, T upperClamp = 0, T lowerClamp = 0); //Ensure that clampVariable will be in between [lowerClamp,upperClamp]
	int CheckCollision(Vector2f otherPos, Vector2f otherHalfSize);

	void UseItem(int itemID); //Use Item


	bool isAlive = true;

	string name = "Unset Name";
	string type = "Unset Type";
	int currentLevel = 0;
	int currentHp = 0;
	int currentExp = 0;
	int currentHappiness = 0;
	int currentFood = 0;
	int currentPoop = 0;

	float hpChangeRateMultiplier = 1.0f;
	float expChangeMultiplier = 1.0f;
	float foodChangeMultiplier = 1.0f;
	float happinessChangeMultiplier = 1.0f;
	float poopChangeMultiplier = 1.0f;

	bool ateEvolveStone = false;


	Vector2f speed = Vector2f(0,0);
	Vector2f maxSpeed = Vector2f(5,5);

	float randomMovementInterval = 5;
	float randomMovementIntervalTime = 0;
	float randomMovementMoveTime = 2;
	float randomMovementMoveTotalTime = 0;
	bool isRandomlyMoving = false;
	Vector2f randomMoveSpeed = Vector2f(0, 0);

//vector<Item>  inventory;


//private:
	float totalTime = 0;
	int tickTime = 1;

	int levelMax = 0;
	vector<int> hpMax; //HP
	vector<int> expPerEvolve; //EXP
	vector<int> happinessMax; //Happiness
	vector<int> foodMax; //Food
	vector<int> poopMax; //Poop

	//All Rate are at 1 per X tickTime(seconds);
	int hpChangeRate = 1;
	int expChangeRate = 1;
	int foodChangeRate = 1;
	int happinessChangeRate = 1;
	int poopChangeRate = 1;

	float notEnoughFoodThreshold = 0.2f; //If Food is BELOW currentFood * this multiplier, HP , Happiness , starts to decay

};

