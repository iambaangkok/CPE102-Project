#include <SFML/Graphics.hpp>
#include "PlatformObject.h"
#include "GameObject.h"
#include <ctime>
#include <cstdlib>
#include <random>

PlatformObject::PlatformObject(Vector2f size, Vector2i windowSize, int NO_OF_PLATFORM , string filepath)
{
	this->size = size;
	this->windowSize = windowSize;
	this->NO_OF_PLATFORM = NO_OF_PLATFORM;
	
	platformtexture.loadFromFile(filepath);
	platform.rectangleShape.setTexture(&platformtexture, true);
	
	platform.SetDimensions(size);
	platform.SetOrigin(size / 2.0f);
	int part = 1040 / NO_OF_PLATFORM;
	for (unsigned int i = 0; i < NO_OF_PLATFORM; ++i) {
		float ux = (rand() % (720 - (int)size.x)) + size.x / 2.0f;
		float uy = rand() % (part/3) + part/3.0f + i * part - 600.0f;
		platformPos.push_back(Vector2f(ux, uy));
		enabled.push_back(true);
		pass.push_back(false);
	}
}

PlatformObject::~PlatformObject()
{
}

void PlatformObject::Initialize() {
	int part = 1040 / NO_OF_PLATFORM;
	for (unsigned int i = 0; i < NO_OF_PLATFORM; ++i) {
		float ux = (rand() % (720 - (int)size.x)) + size.x / 2.0f;
		float uy = rand() % (part / 3) + part / 3.0f + i * part - 600.0f;
		platformPos[i] = Vector2f(ux, uy);
		enabled[i] = true;
		pass[i] = false;
	}
}

void PlatformObject::Draw(RenderWindow& window , int difficulty)
{
	for (unsigned int i = 0; i < NO_OF_PLATFORM; ++i) {
		if (difficulty != prev) {
			prev = difficulty;
			int random = rand() % NO_OF_PLATFORM;
			while (!enabled[random]) {
				random = rand() % NO_OF_PLATFORM;
			}
			enabled[random] = false;
		}
		platform.SetPosition(platformPos[i]);
		if(enabled[i] || !pass[i])
			platform.Draw(window);
	}
}
