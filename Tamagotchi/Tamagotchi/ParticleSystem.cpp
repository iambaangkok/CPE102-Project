#include "ParticleSystem.h"
ParticleSystem::ParticleSystem() {

}
ParticleSystem::ParticleSystem(int rate, float spread, float angleOngsa, float lifetime, float speed
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
		randAngle  = rand() % angleDiff + minAngle;
		randedAngle.push_back(randAngle);
	}
}

void ParticleSystem::Update(float deltaTime) {

	Move();

}

void ParticleSystem::Draw(RenderWindow& window) {

	for (int i = 0; i < numberOfParticle; ++i) {
		amoutOfParticle[i].Draw(window);
	}
	


}

void ParticleSystem::Move() {

	for (int i = 0; i < numberOfParticle; ++i) {
		angleOngsa = randedAngle[i];
		angleRadian = angleOngsa * (3.1415926 / 180);
		speedx = speed * cos(angleRadian);
		speedy = speed * sin(angleRadian);

		amoutOfParticle[i].Move(speedx, speedy);
	}
	
}

ParticleSystem::~ParticleSystem() {

}