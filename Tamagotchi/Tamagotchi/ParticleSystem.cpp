#include "ParticleSystem.h"
ParticleSystem::ParticleSystem() {

}
ParticleSystem::ParticleSystem(int rate, float spread, float angle, float lifetime, float speed
, Vector2f dimensions, Vector2f position, string texturePath, Vector2u imageCount, Vector2i start, Vector2i finish, float frameTime) {
	this->rate = rate;
	this->spread = spread;
	this->angle = angle;
	this->lifetime = lifetime;
	this->speed = speed;

	static GameObject emitter = GameObject(position, dimensions, true, texturePath
	, imageCount, start, finish , frameTime);
	
	

	numberOfParticle = rate * lifetime;
	minAngle = angle - spread;
	maxAngle = angle + spread;

	for (int i = 0; i < numberOfParticle; ++i) {
		amoutOfParticle.push_back(emitter);
	}	
}

void ParticleSystem::Draw(RenderWindow& window) {

	for (int i = 0; i < numberOfParticle; ++i) {
		amoutOfParticle[i].Draw(window);
	}
	


}
ParticleSystem::~ParticleSystem() {

}