#include <SFML/Graphics.hpp>
#include "PlatformObject.h"
#include "GameObject.h"
#include <ctime>
#include <cstdlib>
#include <random>

PlatformObject::PlatformObject(Vector2f size, Vector2i windowSize, int NO_OF_PLATFORM)
{
	this->size = size;
	this->windowSize = windowSize;
	this->NO_OF_PLATFORM = NO_OF_PLATFORM;
	
	platformtexture.loadFromFile("Assets/Textures/platform.png");
	platform.rectangleShape.setTexture(&platformtexture, true);
	//platform.SetTexture(platformtexture);
	
	platform.SetDimensions(size);
	platform.SetOrigin(size / 2.0f);
}

PlatformObject::~PlatformObject()
{
}

void PlatformObject::Initialize()
{
	int part = 1040 / NO_OF_PLATFORM;
	for (unsigned int i = 0; i < NO_OF_PLATFORM; ++i) {
		float ux = (rand() % (720 - 2 * (int)size.x)) + size.x;
		float uy = rand() % (part - 30) + 15 + i*part; 
		platformPos.push_back(Vector2f(ux, uy));
		enabled.push_back(true);
	}
}

void PlatformObject::Draw(RenderWindow& window , int difficulty)
{
	for (unsigned int i = 0; i < NO_OF_PLATFORM; ++i) {
		if (difficulty != prev) {
			prev = difficulty;
			int random = rand() % NO_OF_PLATFORM;
			while (!enabled[rand() % NO_OF_PLATFORM]) {
				random = rand() % NO_OF_PLATFORM;
			}
			enabled[random] = false;
		}
		platform.SetPosition(platformPos[i]);
		platform.Draw(window);
	}
}
