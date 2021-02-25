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


void Pet::Update(float deltaTime, unordered_map<string, bool>& keyPress, unordered_map<string, bool>& keyHold, unordered_map<string, bool>& keyRelease,
	unordered_map<string, bool>& mousePress, unordered_map<string, bool>& mouseRelease, Vector2i mousePosition, int mouseWheelDelta)
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
	if (shadowYOffset > shadowNormalYOffset) {
		isInAir = true;
	}
	else if (shadowYOffset == shadowNormalYOffset) {
		isInAir = false;
	}

	

	if (isAlive) {
		//Manual Input will override random movement
		if (keyHold["W"]) {
			speed.y = -maxSpeed.y;
			randomMovementIntervalTime = randomMovementMoveTotalTime = 0;
			isRandomlyMoving = false;
		}
		if (keyHold["A"]) {
			speed.x = -maxSpeed.x;
			randomMovementIntervalTime = randomMovementMoveTotalTime = 0;
			isRandomlyMoving = false;
		}
		if (keyHold["S"]) {
			speed.y = +maxSpeed.y;
			randomMovementIntervalTime = randomMovementMoveTotalTime = 0;
			isRandomlyMoving = false;
		}
		if (keyHold["D"]) {
			speed.x = +maxSpeed.x;
			randomMovementIntervalTime = randomMovementMoveTotalTime = 0;
			isRandomlyMoving = false;
		}
		if (keyHold["LSHIFT"]) {
			speed.x *= runSpeedMultiplier;
			speed.y *= runSpeedMultiplier;
		}
		if (keyHold["SPACE"]) {
			if (!isInAir) {
				shadowYOffsetSpeed = jumpAcceleration;
				isInAir = true;
			}
		}
		if (mousePress["M1"]) {
			shadow->SetPosition(Vector2f(mousePosition.x, mousePosition.y));
			randomMovementIntervalTime = randomMovementMoveTotalTime = 0;
			isRandomlyMoving = false;
			if (IsMouseOver(mousePosition)) {
				
				
			}
			
		}
		//Calculate Random Movement
		if (randomMovementIntervalTime > randomMovementInterval) {
			isRandomlyMoving = true;
			randomMovementIntervalTime -= randomMovementInterval;

			float moveAngleDegree = rand() % 360;
			float moveAngleRadian = moveAngleDegree * 3.14159 / 180;

			randomMoveSpeed = Vector2f(maxSpeed.x*cos(moveAngleRadian),maxSpeed.y*sin(moveAngleRadian));
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

		shadow->Move(speed.x, speed.y);
		SetPosition(shadow->GetPosition().x, shadow->GetPosition().y - shadowYOffset - shadow->GetDimensions().y/2);

		for (int i = 0; i < shadowBorder.size(); ++i) {
			int shadowCollision = shadow->CheckCollision(shadowBorder[i]);
			if (shadowCollision == 1) { //Right Collide
				shadow->SetPosition(shadowBorder[i].GetPosition().x - shadowBorder[i].GetDimensions().x/2 - shadow->GetDimensions().x / 2, shadow->GetPosition().y);
			}
			else if (shadowCollision == 2) { //Left Collide
				shadow->SetPosition(shadowBorder[i].GetPosition().x + shadowBorder[i].GetDimensions().x/2 + shadow->GetDimensions().x / 2, shadow->GetPosition().y);
			}
			else if (shadowCollision == 3) { //Bottom Collide
				shadow->SetPosition(shadow->GetPosition().x, shadowBorder[i].GetPosition().y - shadowBorder[i].GetDimensions().y/2 - shadow->GetDimensions().y/2);
			}
			else if (shadowCollision == 4) { //Top Collide
				shadow->SetPosition(shadow->GetPosition().x, shadowBorder[i].GetPosition().y + shadowBorder[i].GetDimensions().y/2 + shadow->GetDimensions().y/2);
			}
		}

		if (speed.x > 0) {
			faceRight = true;
		}
		if (speed.x < 0) {
			faceRight = false;
		}

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
		isMoving = (speed != Vector2f(0, 0));

		//Move ShadowYOffset
		shadowYOffset += shadowYOffsetSpeed * deltaTime;
		if (isInAir) {
			shadowYOffsetSpeed -= gravity * deltaTime;
		}
		else {
			shadowYOffsetSpeed = 0;
		}
		Clamp(&shadowYOffset, 500.0f,shadowNormalYOffset);


		cout << shadowYOffsetSpeed << " " << shadowYOffset << endl;

	}



	//Set Animation according to pet state
	if (isInAir) {
		animation.freezeFrame = true;
		if (shadowYOffsetSpeed > 20) {
			animation.SetFrame(3, 0);
		}
		else if (shadowYOffsetSpeed < -20) {
			animation.SetFrame(4, 0);
		}
		else {
			animation.SetFrame(0, 0);
		}
	}
	else if (isMoving) {
		animation.freezeFrame = false;
		animation.SetStartFinishFrame(1, 0, 2, 0);
	}
	else {
		animation.freezeFrame = false;
		animation.SetStartFinishFrame(0, 0, 0, 0);
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

void Pet::Draw(RenderWindow& window) {
	shadow->Draw(window);
	/*for (int i = 0; i < shadowBorder.size(); ++i) {
		shadowBorder[i].Draw(window);
	}*/
	window.draw(rectangleShape);

}


bool Pet::IsMouseOver(Vector2i& mousePosition) {

	Vector2f posi = GetPosition();
	Vector2f dimen = GetDimensions();
	Vector2f a = Vector2f(posi.x, posi.y);
	Vector2f b = Vector2f(posi.x + dimen.x, posi.y + dimen.y);

	if (mousePosition.x > a.x && mousePosition.x < b.x && mousePosition.y > a.y && mousePosition.y < b.y) {
		return true;
	}
	return false;
}