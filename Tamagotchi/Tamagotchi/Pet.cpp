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

	if (type == "PERRY") {
		hpMax = vector<float>{ 150, 260, 300 };
		expPerEvolve = vector<float>{ 100, 200, 300 };
		happinessMax = vector<float>{ 100, 120, 140 };
		foodMax = vector<float>{ 200, 300, 400 };
		poopMax = vector<float>{ 60, 80, 100 };
		hpChangeRate = 0.05;
		expChangeRate = 0.02;
		foodChangeRate = 0.05;
		happinessChangeRate = baseHappinessChangeRate = 0.02;
		poopChangeRate = 0.1;
		notEnoughFoodThreshold = 0.2f;
	}
	else if (type == "DICKO") {
		hpMax = vector<float>{ 150, 250, 500 };
		expPerEvolve = vector<float>{ 100, 200, 300 };
		happinessMax = vector<float>{ 100, 120, 140 };
		foodMax = vector<float>{ 400, 550, 700 };
		poopMax = vector<float>{ 80, 90, 100 };
		hpChangeRate = 0.05;
		expChangeRate = 0.02;
		foodChangeRate = 0.05;
		happinessChangeRate = baseHappinessChangeRate = 0.02;
		poopChangeRate = 0.1;
		notEnoughFoodThreshold = 0.2f;
	}
	else if (type == "CROK") {
		hpMax = vector<float>{ 200, 300, 400 };
		expPerEvolve = vector<float>{ 100, 200, 300 };
		happinessMax = vector<float>{ 100, 120, 140 };
		foodMax = vector<float>{ 200, 250, 350 };
		poopMax = vector<float>{ 30, 25, 20 };
		hpChangeRate = 0.05;
		expChangeRate = 0.02;
		foodChangeRate = 0.05;
		happinessChangeRate = baseHappinessChangeRate = 0.02;
		poopChangeRate = 0.1;
		notEnoughFoodThreshold = 0.2f;
	}
	else if (type == "GYOZA") {
		hpMax = vector<float>{ 100, 90, 80 };
		expPerEvolve = vector<float>{ 20, 30, 40 };
		happinessMax = vector<float>{ 100, 120, 140 };
		foodMax = vector<float>{ 50, 60, 70 };
		poopMax = vector<float>{ 50, 80, 100 };
		hpChangeRate = 0.2;
		expChangeRate = 0.1;
		foodChangeRate = 0.1;
		happinessChangeRate = baseHappinessChangeRate = 0.1;
		poopChangeRate = 0.1;
		notEnoughFoodThreshold = 0.2f;
	}
	else {
		cout << "Invalid Pet Type" << endl;
	}

	float multi = 10;
	hpChangeRate *= multi;
	expChangeRate *= multi;
	foodChangeRate *= multi;
	happinessChangeRate *= multi;
	poopChangeRate *= multi;


	currentLevel = 0;
	currentHp = hpMax[currentLevel];
	currentExp = expPerEvolve[currentLevel];
	currentHappiness = happinessMax[currentLevel];
	currentFood = foodMax[currentLevel];
	currentPoop = 0;
	ateEvolveStone = false;
	money = 0;

	soundBuffers = vector<SoundBuffer>(sfxVariables.size(), SoundBuffer());
	for (int i = 0; i < sfxVariables.size(); ++i) {
		if (soundBuffers[i].loadFromFile(sfxVariables[i].filePath)) {
			cout << "Loaded SFX " << sfxVariables[i].filePath << endl;
		}
		else {
			cout << "Failed to load SFX " << sfxVariables[i].filePath << endl;
		}
		sfx.push_back(Sound(soundBuffers[i]));
		sfx[i].setVolume(sfxVariables[i].volume);
	}
	
	particleSystems.push_back(new ParticleSystem(8, 40, -170, 0.5, 2, Vector2f(10, 10), position, "Assets/Textures/ps_pet_airburst_walk.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 1, position.y, 999, false));
	particleSystems[0]->gravity = -0.5;
	particleSystems[0]->spawning_on = false;
	
}

Pet::~Pet()
{
}

void Pet::Initialize() {
	speed = Vector2f(0, 0);
	mouseIsOver = false;
	happinessChangeRate = baseHappinessChangeRate;
	evolveButtonClicked = false;
	particleSystems[0]->spawning_on = false;
}


void Pet::Update(float deltaTime, unordered_map<string, bool>& keyPress, unordered_map<string, bool>& keyHold, unordered_map<string, bool>& keyRelease,
	unordered_map<string, bool>& mousePress, unordered_map<string, bool>& mouseRelease, unordered_map<string, bool>& mouseHold, Vector2i mousePosition, int mouseWheelDelta)
{
	time_currentTime_sinceEpoch = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count(); //Update every frame
	time_currentSession = time_currentTime_sinceEpoch - time_lastSession; //Update every frame
	time_alive = time_currentTime_sinceEpoch - time_sinceBirth; //READ FROM FILE ONCE & Update every frame

	//cout << time_sinceBirth << " " << time_lastSession << " " << time_sinceLastSession << " " << time_currentTime_sinceEpoch << " " << time_currentSession << " " << time_alive << " " << endl;

	if (!enabled) {
		return;
	}

	if (currentHp < 0) {
		isAlive = false;
	}

	totalTime += deltaTime;
	randomMovementIntervalTime += deltaTime;
	isInAirLastFrame = isInAir;
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
				//particleSystems.push_back(new ParticleSystem(10, 10, 90, 1, 3, Vector2f(15, 15), Vector2f(shadow->GetPosition().x, shadow->GetPosition().y), "Assets/Textures/ps_pet_airburst.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 1, shadow->GetPosition().y, 2, false, true));
				//particleSystems[particleSystems.size() - 1]->gravity = -2;
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
		if (keyPress["R"]) {
			currentPoop = poopMax[currentLevel] - 0.5;
		}
		if (keyPress["F"]) {
			currentExp = expPerEvolve[currentLevel] - 0.5;
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
			//cout << "MOUSE RELEASE" << " " << throwSpeed.x  << " "  << shadowYOffsetSpeed << endl << endl << endl;
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
		


		

		/// Still Alive and Growing
		//Calculate stats
		//if (totalTime > tickTime) {
		//	totalTime -= tickTime;

		if ((float)currentFood < (float)foodMax[currentLevel] * notEnoughFoodThreshold) { // Not Enough Food
			currentHp -= hpChangeRate * hpChangeRateMultiplier * deltaTime / tickTime;
		}
		else if((float)currentFood < (float)foodMax[currentLevel] * 0.5f){
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

		if (currentExp >= expPerEvolve[currentLevel] && ateEvolveStone && evolveButtonClicked ) {
			currentLevel += 1;
			if (currentLevel > 2) {
				currentLevel = 2;
			}
			currentExp = 0;
			ateEvolveStone = false;
		}

		isMoving = (speed != Vector2f(0, 0));
		//cout << currentLevel << " " << currentHp << " " << currentFood <<  " " << (float)foodMax[currentLevel] * notEnoughFoodThreshold <<  " " << currentPoop << " " << currentExp << " " << currentHappiness << " " <<  endl;
	}

	
	drawLayer = GetSide("BOTTOM");

	


	
	///Set Animation & Play Sound     according to pet state  && ///ParticleSystem

	
	particleSystems[0]->position = shadow->GetPosition();
	particleSystems[0]->floorLine = shadow->GetPosition().y + 20;
	if (deltaPosition.x > 0) {
		faceRight = true;
		if (!isInAir) {
			particleSystems[0]->SetAngle(190);
			particleSystems[0]->spawning_on = true;
			particleSystems[0]->totalTimein1spawn = 0;
		}
		

	}else if (deltaPosition.x < 0) {
		faceRight = false;
		if (!isInAir) {
			particleSystems[0]->SetAngle(-10);
			particleSystems[0]->spawning_on = true;
			particleSystems[0]->totalTimein1spawn = 0;
		}
		
	}
	else {
	}

	//cout << "PS->spon = " << particleSystems[0]->spawning_on << endl;
	

	if (faceRight) {
		rectangleShape.setScale(Vector2f(1, 1));
	}
	else {
		rectangleShape.setScale(Vector2f(-1, 1));
	}
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
	
	if (animation.Update(deltaTime)) {
		if (isMoving) {
			sfx[currentLevel].play();
		}
	}
	if (isInAir && !isInAirLastFrame) {
		if (!isDraggedByMouse) {
			sfx[3].play();
		}
	}
	if (!isInAir && isInAirLastFrame) {
		particleSystems.push_back(new ParticleSystem(5 , 50, 170, 1, 2, Vector2f(10, 10), Vector2f(shadow->GetPosition().x, shadow->GetPosition().y + 5), "Assets/Textures/ps_pet_airburst.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 1, shadow->GetPosition().y+10, 2, true));
		particleSystems[particleSystems.size() - 1]->gravity = -2;
		particleSystems.push_back(new ParticleSystem(5 , 50, 10, 1, 2, Vector2f(10, 10), Vector2f(shadow->GetPosition().x, shadow->GetPosition().y + 5), "Assets/Textures/ps_pet_airburst.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 1, shadow->GetPosition().y+10, 2, true));
		particleSystems[particleSystems.size() - 1]->gravity = -2;
		sfx[4].play();
	}

	for (int i = 0; i < particleSystems.size(); ++i) {
		if (particleSystems[i]->Update(deltaTime)) {
			DeleteParticle(i);
		}
	}

	rectangleShape.setTextureRect(animation.uvRect);


}

void Pet::Draw(RenderWindow& window) {
	shadow->Draw(window);
	/*for (int i = 0; i < shadowBorder.size(); ++i) {
		shadowBorder[i].Draw(window);
	}*/
	window.draw(rectangleShape);
	for (int i = 0; i < particleSystems.size(); ++i) {
		particleSystems[i]->Draw(window);
	}
}

void Pet::PlaySound(Sound& soundPlayer, int soundBufferIndex, string type) {
	cout << "Playing " << type << " : " << soundBufferIndex << endl;
	soundPlayer.setVolume(sfxVariables[soundBufferIndex].volume);
	soundPlayer.setBuffer(soundBuffers[soundBufferIndex]);
	soundPlayer.play();
}

bool Pet::CanPoop() {
	return currentPoop >= poopMax[currentLevel];
}
Poop* Pet::CreatePoop() {
	Poop* newPoop = new Poop(GetPosition(), Vector2f(110*0.7, 80*0.7), true, "Assets/Textures/pet_poop.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 10, 5, shadow->GetPosition().y);
	currentPoop = 0;
	sfx[rand() % 3 + 5].play();
	return newPoop;
}

void Pet::DeleteParticle(int index)
{
	delete particleSystems[index];
	particleSystems.erase(particleSystems.begin() + index);
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