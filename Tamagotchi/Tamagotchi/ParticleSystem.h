#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "GameObject.h"
using namespace sf;
using std::vector;

class ParticleSystem
{
public:
	ParticleSystem();
	ParticleSystem(int rate, float spread, float angle, float lifetime, float speed
	, Vector2f dimensions, Vector2f position, string texturePath, Vector2u imageCount, Vector2i start, Vector2i finish, float frameTime);
	~ParticleSystem();
	void Initialize();
	void Update(float deltaTime);
	void Draw(RenderWindow &window);

	int rate;
	float spread;
	float angle;
	float lifetime;
	float speed;
	int numberOfParticle; //number of particle in a moment
	float minAngle;
	float maxAngle;
	Vector2f emitterPosition;
	vector<GameObject> amoutOfParticle;
};

