#include "ParticleSystem.h"
ParticleSystem::ParticleSystem() {

}
ParticleSystem::ParticleSystem(float rate, float spread, float angleOngsa, float lifetime, float speed
, Vector2f dimensions, Vector2f position, string texturePath, Vector2u imageCount, Vector2i start, Vector2i finish, float frameTime, float floorLine, bool gravity_on) {
	this->rate = rate;
	this->spread = spread;
	this->angleOngsa = angleOngsa;

	while (this->angleOngsa > 360)
	{
		this->angleOngsa = this->angleOngsa - 360;
	}
	this->lifetime = lifetime;
	this->speed = speed;
	this->position = position;
	this->gravity_on = gravity_on;
	this->floorLine = floorLine;
	static GameObject emitter = GameObject(position, dimensions, true, texturePath
	, imageCount, start, finish , frameTime);
	
	

	numberOfParticle = rate * lifetime;
	minAngle = angleOngsa - spread;
	
	while (minAngle > 360)
	{
		minAngle = minAngle - 360;
	}
	maxAngle = angleOngsa + spread;
	
	while (maxAngle > 360)
	{
		maxAngle = maxAngle - 360;
	}
	angleDiff = maxAngle - minAngle;

	for (int i = 0; i < numberOfParticle; ++i) {
		amoutOfParticle.push_back(emitter);
		float randAngle;
		if (spread != 0) {
			randAngle = rand() % angleDiff + minAngle;
		}
		else
		{
			randAngle = angleOngsa;
		}
		randedAngle.push_back(randAngle);
		totalTime.push_back(lifetime);
		started.push_back(0);
	}
	
	spawnTime = 1/rate;
	currentParticle = 0;
	currentSpawnTime = 0;


	
	for (int i = 0; i < numberOfParticle; ++i)
	{
		angleOngsa = randedAngle[i];
		angleRadian = angleOngsa * (3.1415926 / 180);
		speedx = speed * cos(angleRadian);
		speedy = speed * sin(angleRadian);
		vectorspeedX.push_back(speedx);
		vectorspeedY.push_back(speedy);
	}

}

void ParticleSystem::Update(float deltaTime) {
	if (spawning_on == true) {
		currentSpawnTime = currentSpawnTime + deltaTime;
	}
	for (int i = 0; i < numberOfParticle; ++i) {
		if (currentSpawnTime < (i + 1) * spawnTime && currentSpawnTime > (i)*spawnTime && !started[i]) {
			started[i] = true;
			amoutOfParticle[i].SetPosition(position);
			totalTime[i] = lifetime;
			float randAngle;
			if (spread != 0) {
				randAngle = rand() % angleDiff + minAngle;
			}
			else
			{
				randAngle = angleOngsa;
			}
			randedAngle[i] = randAngle;
			angleOngsa = randedAngle[i];
			angleRadian = angleOngsa * (3.1415926 / 180);
			speedx = speed * cos(angleRadian);
			speedy = speed * sin(angleRadian);
			vectorspeedX[i] = speedx;
			vectorspeedY[i] = speedy;
		}
		if (started[i] == true) {
			currentParticle = i;
			if (gravity_on == true) {
				vectorspeedY[i] = vectorspeedY[i] + gravity * deltaTime;
			}
			Move();
			if (amoutOfParticle[i].GetPosition().y + amoutOfParticle[i].GetDimensions().y/2 >= floorLine) {
				vectorspeedY[i] = 0;
				amoutOfParticle[i].SetPosition(amoutOfParticle[i].GetPosition().x, floorLine - amoutOfParticle[i].GetDimensions().y / 2);
			}
			totalTime[i] = totalTime[i] - deltaTime;
		}
	}

	for (int i = 0; i < numberOfParticle; ++i) {
		if (spawning_on == true) {
			if (totalTime[i] <= 0) {
				started[i] = false;
			}
		}
	}

	if (currentSpawnTime > spawnTime * numberOfParticle) {
		currentSpawnTime -= spawnTime * numberOfParticle;
	}

}

void ParticleSystem::Draw(RenderWindow& window) {

	for (int i = 0; i < numberOfParticle; ++i) {
			if (started[i] == 1) {
				amoutOfParticle[i].Draw(window);
			}
	}
	


}

void ParticleSystem::Move() {
		amoutOfParticle[currentParticle].Move(vectorspeedX[currentParticle], vectorspeedY[currentParticle]);
		if(currentParticle < numberOfParticle){
			currentParticle++;
	}
		
}

ParticleSystem::~ParticleSystem() {

}