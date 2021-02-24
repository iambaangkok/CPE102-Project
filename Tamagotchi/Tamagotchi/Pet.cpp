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

void Pet::Initialize() {
	speed = Vector2f(0, 0);
}


void Pet::Update(float deltaTime)
{
	if (!enabled) {
		return;
	}


	if (currentHp < 0) {
		isAlive = false;
	}

	totalTime += deltaTime;
	randomMovementIntervalTime += deltaTime;
	if (isRandomlyMoving) {
		randomMovementMoveTotalTime += deltaTime;
	}
	

	if (isAlive) {
		//Calculate Random Movement
		cout << randomMovementIntervalTime << " " << randomMovementMoveTotalTime << " " << randomMoveSpeed.x << " " << randomMoveSpeed.y << " " << speed.x << " " << speed.y;
		if (randomMovementIntervalTime > randomMovementInterval) {
			isRandomlyMoving = true;
			randomMovementIntervalTime -= randomMovementInterval;

			randomMoveSpeed = Vector2f((rand() % ((int)(maxSpeed.x)+1)) * pow(-1, rand() % 2), (rand() % ((int)(maxSpeed.y) + 1)) * pow(-1, rand() % 2));
		}

		if (isRandomlyMoving) {
			if (randomMovementMoveTotalTime > randomMovementMoveTime) {
				randomMovementMoveTotalTime -= randomMovementMoveTime;
				isRandomlyMoving = false;
				speed = Vector2f(0, 0);
			}
			else {
				speed = randomMoveSpeed;
			}
		}

		//Move
		Move(speed.x, speed.y);
		if (faceRight) {
			rectangleShape.setScale(Vector2f(1, 1));
		}
		else {
			rectangleShape.setScale(Vector2f(-1, 1));
		}


		if (totalTime > tickTime) {//Still Alive and Growing
			totalTime -= tickTime;

			if ((float)currentFood < foodMax[currentLevel] * notEnoughFoodThreshold) { // Not Enough Food
				currentHp -= int(hpChangeRate * hpChangeRateMultiplier);
			}
			else {
				currentHappiness -= int(happinessChangeRate * happinessChangeMultiplier);

			}
			currentExp += int(expChangeRate * expChangeMultiplier);
			currentFood -= int(foodChangeRate * foodChangeMultiplier);
			currentPoop += int(poopChangeRate * poopChangeMultiplier);

			Clamp(&currentHp, hpMax[currentLevel], 0);
			Clamp(&currentHappiness, happinessMax[currentLevel], 0);
			Clamp(&currentExp, expPerEvolve[currentLevel], 0);
			Clamp(&currentFood, foodMax[currentLevel], 0);
			Clamp(&currentPoop, poopMax[currentLevel], 0);
		}
	}

	

	animation.Update(deltaTime);
	rectangleShape.setTextureRect(animation.uvRect);
}

template<typename T>
void Pet::Clamp(T* clampVariable, T upperClamp, T lowerClamp)
{
	if (*clampVariable > upperClamp) *clampVariable = upperClamp;
	if (*clampVariable < lowerClamp) *clampVariable = lowerClamp;
}

void Pet::UseItem(int itemID) {
	//item.Use(this);
}


int Pet::CheckCollision(Vector2f otherPos, Vector2f otherHalfSize)
{
	Vector2f thisPos = GetPosition();
	Vector2f thisHalfSize = GetSize() / 2.0f;

	float deltaX = otherPos.x - thisPos.x;
	float deltaY = otherPos.y - thisPos.y;

	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);
	
	/*
		state : 
			0 - Pet doesn't hit object.
			1 - The right side of pet hit object.
			2 - The left side of pet hit object.
			3 - The bottom side of pet hit object.
			4 - The top side of pet hit object.
	*/

	if (intersectX < 0.0f && intersectY < 0.0f) {
		if (intersectX > intersectY) {
			if (deltaX > 0.0f)
				return 1; 
			else
				return 2;
		}
		else {
			if (deltaY > 0.0f)
				return 3;
			else 
				return 4;
		}
	}
	return 0;
}