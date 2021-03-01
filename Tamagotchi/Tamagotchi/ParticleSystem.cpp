#include "ParticleSystem.h"
ParticleSystem::ParticleSystem() {

}
ParticleSystem::ParticleSystem(float rate, float spread, float angleOngsa, float lifetime, float speed
, Vector2f dimensions, Vector2f position, string texturePath, Vector2u imageCount, Vector2i start, Vector2i finish, float frameTime) {
	this->rate = rate;
	this->spread = spread;
	this->angleOngsa = angleOngsa;

	while (this->angleOngsa > 360)
	{
		this->angleOngsa = this->angleOngsa - 360;
	}
	this->lifetime = lifetime;
	this->speed = speed;

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
		randAngle = rand() % angleDiff + minAngle;
		randedAngle.push_back(randAngle);
		totalTime.push_back(lifetime);
		started.push_back(0);
	}
	
	spawnTime = 1/rate;
	currentParticle = 0;
}

void ParticleSystem::Update(float deltaTime) {
	
	currentSpawnTime = currentSpawnTime + deltaTime;
	for (int i = 0; i < numberOfParticle; ++i) {
		if (currentSpawnTime > (i+1)*spawnTime) {
			started[i] = 1;
			//Move();
			//currentSpawnTime = currentSpawnTime - spawnTime;
		}
		if (started[i] == 1) {
			currentParticle = i;
			Move();
		}
	}

	cout << spawnTime << " " << currentSpawnTime << endl;

}

void ParticleSystem::Draw(RenderWindow& window) {

	for (int i = 0; i < numberOfParticle; ++i) {
		amoutOfParticle[i].Draw(window);

	}
	


}

void ParticleSystem::Move() {

		angleOngsa = randedAngle[currentParticle];
		angleRadian = angleOngsa * (3.1415926 / 180);
		speedx = speed * cos(angleRadian);
		speedy = speed * sin(angleRadian);

		amoutOfParticle[currentParticle].Move(speedx, speedy);
		if(currentParticle < numberOfParticle){
			currentParticle++;
	}
	
}

ParticleSystem::~ParticleSystem() {

}