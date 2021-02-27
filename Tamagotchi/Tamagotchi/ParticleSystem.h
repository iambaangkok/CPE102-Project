#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "GameObject.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace sf;
using std::vector;
using std::cos;
using std::sin;

class ParticleSystem
{
public:
	ParticleSystem();
	ParticleSystem(int rate, float spread, float angleOngsa, float lifetime, float speed
	, Vector2f dimensions, Vector2f position, string texturePath, Vector2u imageCount, Vector2i start, Vector2i finish, float frameTime);
	~ParticleSystem();
	void Initialize();
	void Update(float deltaTime);
	void Draw(RenderWindow &window);
	void Move();

	int rate;
	float spread;
	float angleOngsa;
	float angleRadian;
	float lifetime;
	float speed;
	int numberOfParticle; //number of particle in a moment
	float minAngle;
	float maxAngle;
	int angleDiff;
	Vector2f emitterPosition;
	vector<GameObject> amoutOfParticle;
	vector<float> randedAngle;
	float speedx;
	float speedy;
};

