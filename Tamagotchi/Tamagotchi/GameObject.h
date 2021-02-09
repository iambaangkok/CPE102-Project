#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

using namespace sf;


class GameObject
{
public:
	GameObject(Vector2f position, Vector2f dimensions, bool originIsCenter, String texturePath); //Single Texture
	GameObject(Vector2f position, Vector2f dimensions, bool originIsCenter, 
		String texturePath, Vector2u imageCount, float frameTime); //Animation from Texture Sheet
	GameObject(Vector2f position, Vector2f dimensions, bool originIsCenter,
		String texturePath, Vector2u imageCount,float frameTime, Vector2u uv); //Single Texture from Texture Sheet
	~GameObject();

	void Update(float deltaTime);
	void Draw(RenderWindow window);
	Vector2f GetPosition();

	bool enabled = true;

	Vector2f dimensions;


	Texture texture;
	RectangleShape rectangleShape;

	Animation animation;


private:


};


