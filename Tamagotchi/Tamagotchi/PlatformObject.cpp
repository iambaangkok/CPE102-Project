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
	for (unsigned int i = 0 ; i < NO_OF_PLATFORM; ++i) {
		GameObject A;
		platform.push_back(A);
		platform[i].SetDimensions(size);
		platform[i].SetOrigin(size / 2.0f);
		platform[i].rectangleShape.setFillColor(Color::Yellow);
		platform[i].rectangleShape.setOutlineColor(Color::Red);
		platform[i].rectangleShape.setOutlineThickness(2.0f);

	}
}

PlatformObject::~PlatformObject()
{
}

void PlatformObject::Initialize()
{

	std::uniform_int_distribution<unsigned> x(size.x, 720 - size.x);
	std::uniform_int_distribution<unsigned> y(100, 940);
	std::default_random_engine e(time(0));

	for (unsigned int i = 0; i < NO_OF_PLATFORM; ++i) {
		float ux = static_cast<float>(x(e));
		float uy = static_cast<float>(y(e));
		platform[i].SetPosition(Vector2f(ux, uy));
	}
}

void PlatformObject::Update()
{
}

void PlatformObject::Draw(RenderWindow& window)
{
	for (unsigned int i = 0; i < NO_OF_PLATFORM; ++i) {
		platform[i].Draw(window);
	}
}
