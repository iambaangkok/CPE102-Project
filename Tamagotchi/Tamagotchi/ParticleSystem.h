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
	ParticleSystem(float rate, float spread, float angleOngsa, float lifetime, float speed
	, Vector2f dimensions, Vector2f position, string texturePath, Vector2u imageCount, Vector2i start, Vector2i finish, float frameTime, float floorLine, bool gravity_on = true);
	~ParticleSystem();
	void Initialize();
	void Update(float deltaTime);
	void Draw(RenderWindow &window);
	void Move();
	
	Vector2f position;
	float rate; //number of particle that spawn in one second.
	float spread; //the spread of the angle.
	float angleOngsa; //angle in degree.
	float angleRadian; //angle in radian.
	float lifetime; //lifetime of particle.
	float speed; //speed of particle.
	int numberOfParticle; //number of particle in a moment.
	float minAngle; //the minimum angle that particle can spread.
	float maxAngle; //the maximum angle that particle can spread.
	int angleDiff; //max angle - min angle.
	vector<GameObject> amoutOfParticle; //amount of particle that had been created.
	vector<float> randedAngle; //randomed angle.
	vector<float> totalTime; //lifetime of one particle.
	int currentParticle = 0;
	float spawnTime = 0;
	float currentSpawnTime = 0;
	vector<bool> started;
	float speedx; //speed in x.
	float speedy; //speed in y.
	vector<float> vectorspeedY;
	vector<float> vectorspeedX;
	float gravity = 9.8;
	bool gravity_on;
	float floorLine;
	bool spawning_on = true;
};

