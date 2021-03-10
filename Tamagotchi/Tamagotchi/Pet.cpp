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
	string name, string type, int levelMax, vector<float> hpMax, vector<float> expPerEvolve, vector<float> happinessMax, vector<float> foodMax, vector<float> poopMax,
	int hpChangeRate, int expChangeRate, int foodChangeRate, int happinessChangeRate, int poopChangeRate, float notEnoughFoodThreshold)
	: GameObject(position, dimensions, originIsCenter, texturePath, imageCount, start, finish, frameTime)
{
	this->name = name;
	this->type = type;
	this->levelMax = levelMax;
	currentLevel = 0;
	this->hpMax = hpMax;
	currentHp = this->hpMax[currentLevel];
	this->expPerEvolve = expPerEvolve;
	currentExp = expPerEvolve[currentLevel];
	this->happinessMax = happinessMax;
	currentHappiness = this->happinessMax[currentLevel];
	this->foodMax = foodMax;
	currentFood = this->foodMax[currentLevel];
	this->poopMax = poopMax;
	currentPoop = 0;
	this->hpChangeRate = hpChangeRate;
	this->expChangeRate = expChangeRate;
	this->foodChangeRate = foodChangeRate;
	this->happinessChangeRate = happinessChangeRate;
	this->poopChangeRate = poopChangeRate;
	this->notEnoughFoodThreshold = notEnoughFoodThreshold;
	ateEvolveStone = false;
	money = 0;
}

Pet::Pet(Vector2f position, Vector2f dimensions, bool originIsCenter,//By Type
	string texturePath, Vector2u imageCount, Vector2i start, Vector2i finish, float frameTime,
	string name, string type) : GameObject(position, dimensions, originIsCenter, texturePath, imageCount, start, finish, frameTime)
{
	this->name = name;
	this->type = type;
	levelMax = 3;
	if (type == "Perry") {
		hpMax = vector<float>{ 100, 150, 200 };
		expPerEvolve = vector<float>{ 100, 200, 300 };
		happinessMax = vector<float>{ 100, 120, 140 };
		foodMax = vector<float>{ 100, 120, 140 };
		poopMax = vector<float>{ 80, 90, 100 };
		hpChangeRate = 5;
		expChangeRate = 5;
		foodChangeRate = 5;
		happinessChangeRate = baseHappinessChangeRate = 5;
		poopChangeRate = 5;
		notEnoughFoodThreshold = 0.2f;
	}
	else if (type == "Dicko") {
		hpMax = vector<float>{ 100, 150, 200 };
		expPerEvolve = vector<float>{ 100, 200, 300 };
		happinessMax = vector<float>{ 100, 120, 140 };
		foodMax = vector<float>{ 100, 120, 140 };
		poopMax = vector<float>{ 80, 90, 100 };
		hpChangeRate = 1;
		expChangeRate = 1;
		foodChangeRate = 1;
		happinessChangeRate = baseHappinessChangeRate = 1;
		poopChangeRate = 1;
		notEnoughFoodThreshold = 0.2f;
	}
	else if (type == "Crok") {
		hpMax = vector<float>{ 100, 150, 200 };
		expPerEvolve = vector<float>{ 100, 200, 300 };
		happinessMax = vector<float>{ 100, 120, 140 };
		foodMax = vector<float>{ 100, 120, 140 };
		poopMax = vector<float>{ 80, 90, 100 };
		hpChangeRate = 5;
		expChangeRate = 5;
		foodChangeMultiplier = 5;
		happinessChangeRate = baseHappinessChangeRate = 5;
		poopChangeRate = 5;
		notEnoughFoodThreshold = 0.2f;
	}
	else if (type == "Gyoza") {
		hpMax = vector<float>{ 100, 150, 200 };
		expPerEvolve = vector<float>{ 100, 200, 300 };
		happinessMax = vector<float>{ 100, 120, 140 };
		foodMax = vector<float>{ 100, 120, 140 };
		poopMax = vector<float>{ 80, 90, 100 };
		hpChangeRate = 5;
		expChangeRate = 5;
		foodChangeRate = 5;
		happinessChangeRate = baseHappinessChangeRate = 5;
		poopChangeRate = 5;
		notEnoughFoodThreshold = 0.2f;
	}
	currentLevel = 0;
	currentHp = hpMax[currentLevel];
	currentExp = expPerEvolve[currentLevel];
	currentHappiness = happinessMax[currentLevel];
	currentFood = foodMax[currentLevel];
	currentPoop = 0;
	ateEvolveStone = false;
	money = 0;

}

Pet::~Pet()
{
}

void Pet::Initialize() {
	speed = Vector2f(0, 0);
	mouseIsOver = false;
	happinessChangeRate = baseHappinessChangeRate;
}


void Pet::Update(float deltaTime, unordered_map<string, bool>& keyPress, unordered_map<string, bool>& keyHold, unordered_map<string, bool>& keyRelease,
	unordered_map<string, bool>& mousePress, unordered_map<string, bool>& mouseRelease, unordered_map<string, bool>& mouseHold, Vector2i mousePosition, int mouseWheelDelta)
{
	time_currentTime_sinceEpoch = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count(); //Update every frame
	time_currentSession = time_currentTime_sinceEpoch - time_lastSession; //Update every frame
	time_alive = time_currentTime_sinceEpoch - time_sinceBirth; //READ FROM FILE ONCE & Update every frame

	cout << time_sinceBirth << " " << time_lastSession << " " << time_sinceLastSession << " " << time_currentTime_sinceEpoch << " " << time_currentSession << " " << time_alive << " " << endl;

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
	mouseIsOver = IsMouseOver(mousePosition);
	lastFramePosition = GetPosition();
	

	if (isAlive) {
		///Manual Input will override random movement
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
		if (keyPress["Q"]) {
			currentLevel += 1;
			Clamp(&currentLevel, 2, 0);
		}
		if (keyPress["E"]) {
			currentLevel -= 1;
			Clamp(&currentLevel, 2, 0);
		}
		if (mouseHold["M1"]) {
			if (mouseIsOver) {
				if (!isDraggedByMouse) {
					mousePositionRelativeToPet = GetPosition() - Vector2f(mousePosition.x, mousePosition.y);
					isDraggedByMouse = true;
				}
				if (isDraggedByMouse) {
					randomMovementIntervalTime = randomMovementMoveTotalTime = 0;
					isRandomlyMoving = false;
				}
			}

		}

		if (mouseIsOver && !mouseHold["M1"]) {
			isDraggedByMouse = false;
		}

		if (mouseRelease["M1"]) {
			throwSpeed.x = deltaPosition.x/2 * 30;
			throwSpeed.y = -deltaPosition.y/2 * 30;
			shadowYOffsetSpeed = throwSpeed.y;
			cout << "MOUSE RELEASE" << " " << throwSpeed.x  << " "  << shadowYOffsetSpeed << endl << endl << endl;
		}
		

		///Calculate Random Movement
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

		if (isDraggedByMouse) {
			float shadowX = mousePosition.x + mousePositionRelativeToPet.x;
			Clamp(&shadowX, 720 - shadow->GetDimensions().x / 2, shadow->GetDimensions().x / 2);
			shadow->SetPosition(shadowX, shadow->GetPosition().y);
			SetPosition(shadow->GetPosition().x, std::min(shadow->GetPosition().y - shadowNormalYOffset - shadow->GetDimensions().y / 2, mousePosition.y + mousePositionRelativeToPet.y) );
			shadowYOffset = shadow->GetPosition().y - shadow->GetDimensions().y / 2 - GetPosition().y;
			if (shadowYOffset > shadowNormalYOffset) 
				isInAir = true;
			else if (shadowYOffset == shadowNormalYOffset)
				isInAir = false;

			shadowYOffsetSpeed = 0;
		}
		else {

			if (isInAir) {
				speed.x += throwSpeed.x;
				
				if ( abs(throwSpeed.x -windResistance*deltaTime) < windResistance*deltaTime)  {
					throwSpeed.x = 0;
				}
				else if (throwSpeed.x > 0) {
					throwSpeed.x -= windResistance * deltaTime;
				}
				else if (throwSpeed.x < 0) {
					throwSpeed.x += windResistance * deltaTime;
				}
			}
			else {
				throwSpeed = Vector2f(0, 0);
			}

			shadow->speed = speed;
			shadow->Update(deltaTime);
			SetPosition(shadow->GetPosition().x, shadow->GetPosition().y - shadowYOffset - shadow->GetDimensions().y / 2);

		}
		

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


		///Move ShadowYOffset
		if (!isDraggedByMouse) {
			shadowYOffset += shadowYOffsetSpeed * deltaTime;
			if (isInAir) {
				shadowYOffsetSpeed -= gravity * deltaTime;
			}
			else {
				shadowYOffsetSpeed = 0;
			}
		}

		Clamp(&shadowYOffset, 800.0f, shadowNormalYOffset);
		Vector2f shadowPos = shadow->GetPosition();
		Vector2f shadowDim = shadow->GetDimensions();
		Clamp(&shadowPos.x, 720.0f-shadowDim.x/2, 0.0f+shadowDim.x / 2);
		shadow->SetPosition(shadowPos.x, shadowPos.y);

		
		deltaPosition = GetPosition() - lastFramePosition;
		


		if (deltaPosition.x > 0) {
			faceRight = true;
		}
		if (deltaPosition.x < 0) {
			faceRight = false;
		}

		if (faceRight) {
			rectangleShape.setScale(Vector2f(1, 1));
		}
		else {
			rectangleShape.setScale(Vector2f(-1, 1));
		}

		/// Still Alive and Growing
		//Calculate stats
		//if (totalTime > tickTime) {
		//	totalTime -= tickTime;

			if ((float)currentFood < (float)foodMax[currentLevel] * notEnoughFoodThreshold) { // Not Enough Food
				currentHp -= hpChangeRate * hpChangeRateMultiplier * deltaTime / tickTime;
			}
			else {
				happinessChangeRate -= baseHappinessChangeRate;
			}

			happinessPoint = (float)currentHappiness / happinessMax[currentLevel];
			if (happinessPoint > 210 / 310.0f) {
				expChangeMultiplier = 1;
			}
			else if (happinessPoint > 120 / 310.0f) {
				expChangeMultiplier = 0.8;
			}
			else if (happinessPoint > 50 / 310.0f) {
				expChangeMultiplier = 0.6;
			}
			else if (happinessPoint >= 0) {
				expChangeMultiplier = 0.3;
			}


			currentExp += expChangeRate * expChangeMultiplier * deltaTime / tickTime;
			currentFood -= foodChangeRate * foodChangeMultiplier * deltaTime / tickTime;
			currentHappiness -= happinessChangeRate * happinessChangeMultiplier * deltaTime / tickTime;
			currentPoop += poopChangeRate * poopChangeMultiplier * deltaTime / tickTime;

			Clamp(&currentHp, hpMax[currentLevel], 0.0f);
			Clamp(&currentHappiness, happinessMax[currentLevel], 0.0f);
			Clamp(&currentExp, expPerEvolve[currentLevel], 0.0f);
			Clamp(&currentFood, foodMax[currentLevel], 0.0f);
			Clamp(&currentPoop, poopMax[currentLevel], 0.0f);
		//}
		//isMoving = (speed != Vector2f(0, 0));

		

		
		//cout << currentLevel << " " << currentHp << " " << currentFood <<  " " << (float)foodMax[currentLevel] * notEnoughFoodThreshold <<  " " << currentPoop << " " << currentExp << " " << currentHappiness << " " <<  endl;

	}

	drawLayer = GetSide("BOTTOM");



	///Set Animation according to pet state
	if (isInAir) {
		animation.freezeFrame = true;
		if (deltaPosition.y < -3) {
			animation.SetFrame(3, currentLevel);
		}
		else if (deltaPosition.y > 3) {
			animation.SetFrame(4, currentLevel);
		}
		else {
			animation.SetFrame(0, currentLevel);
		}
	}
	else if (isMoving) {
		animation.freezeFrame = false;
		animation.SetStartFinishFrame(1, currentLevel, 2, currentLevel);
	}
	else {
		animation.freezeFrame = false;
		animation.SetStartFinishFrame(0, currentLevel, 0, currentLevel);
	}
	
	

	animation.Update(deltaTime);
	rectangleShape.setTextureRect(animation.uvRect);





}


bool Pet::CanPoop() {
	return currentPoop >= poopMax[currentLevel];
}
Poop* Pet::CreatePoop() {
	Poop* newPoop = new Poop(GetPosition(), Vector2f(110*0.7, 80*0.7), true, "Assets/Textures/pet_poop.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 10, 5, shadow->GetPosition().y);
	currentPoop = 0;
	return newPoop;
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
	Vector2f a = Vector2f(posi.x - dimen.x/2, posi.y - dimen.y/2);
	Vector2f b = Vector2f(posi.x + dimen.x/2, posi.y + dimen.y/2);

	if (mousePosition.x > a.x && mousePosition.x < b.x && mousePosition.y > a.y && mousePosition.y < b.y) {
		return true;
	}
	return false;
}