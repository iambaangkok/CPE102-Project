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
	platform.SetTexture("Assets/Textures/platform.png");
	platform.SetDimensions(size);
	platform.SetOrigin(size / 2.0f);
}

PlatformObject::~PlatformObject()
{
}

void PlatformObject::Initialize()
{
	for (unsigned int i = 0; i < NO_OF_PLATFORM; ++i) {
		float ux = (rand() % (720 - 2 * (int)size.x)) + size.x;
		float uy = (rand() % (1040 - 2 * (int)size.y)) + size.y;
		platformPos.push_back(Vector2f(ux, uy));
	}
}

void PlatformObject::Update()
{

}

void PlatformObject::Draw(RenderWindow& window)
{
	for (unsigned int i = 0; i < NO_OF_PLATFORM; ++i) {
		platform.SetPosition(platformPos[i]);
		platform.Draw(window);
	}
}
