#pragma once

#include "GravityObject.h"
#include "PlatformObject.h"

class Doodle
{
public :
	Doodle();
	~Doodle();

	void Initialize(PlatformObject &Platform);
	void Update(GravityObject &Alpha , PlatformObject &Platform , RenderWindow& window);
	void Draw(GravityObject& Alpha, PlatformObject& Platform , RenderWindow& window);

	int windowWidth = 720;
	int windowHeight = 1040;

	int score = 0;

};

