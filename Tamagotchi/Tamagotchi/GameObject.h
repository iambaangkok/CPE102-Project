#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Animation.h"

using namespace sf;

using std::cout;
using std::endl;
using std::string;

class GameObject
{
public:
	GameObject(Vector2f position, Vector2f dimensions, bool originIsCenter, 
		string texturePath); //Single Texture
	GameObject(Vector2f position, Vector2f dimensions, bool originIsCenter, 
		string texturePath, Vector2u imageCount, float frameTime); //Animation from Texture Sheet
	//GameObject(Vector2f position, Vector2f dimensions, bool originIsCenter, 
		//string texturePath, Vector2u imageCount,float frameTime, Vector2u uv); //Single Texture from Texture Sheet
	~GameObject();

	void Update(float deltaTime);
	void Update(int row, float deltaTime, bool faceRight);

	void Draw(RenderWindow& window);
	void Move(float speedX, float speedY);

	Vector2f GetPosition();

	bool enabled = true;

	Vector2f dimensions;


	Texture texture;
	RectangleShape rectangleShape;

	Animation animation;


private:


};


