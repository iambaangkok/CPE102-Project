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
	GameObject();
	GameObject(Vector2f position, Vector2f dimensions, bool originIsCenter, 
		string texturePath = "Assets/Textures/testTextureLARGE.png"); //Single Texture
	GameObject(Vector2f position, Vector2f dimensions, bool originIsCenter, 
		string texturePath, Vector2u imageCount, float frameTime); //1Row Animation from Texture Sheet
	GameObject(Vector2f position, Vector2f dimensions, bool originIsCenter, 
		string texturePath, Vector2u imageCount, Vector2i imageCoordinate); //Single Texture from Texture Sheet
	GameObject(Vector2f position, Vector2f dimensions, bool originIsCenter,
		string texturePath, Vector2u imageCount, Vector2i start, Vector2i finish, float frameTime); //Proper Animation
	~GameObject();

	void Update(float deltaTime); //Single Texture
	void Update(int row, float deltaTime, bool faceRight); //1Row Animation, Single Texture from Texture Sheet
	void Update(Vector2i start, Vector2i finish, float deltaTime);//Proper Animation

	void Draw(RenderWindow& window);
	void Move(float speedX, float speedY);//Simple Move

	Vector2f GetPosition(); //Returns Origin position
	Vector2f GetSize();

	void CheckCollision(GameObject &other , float push); //Check if 2 objects collide each other

	bool enabled = true;

	Texture texture;
	RectangleShape rectangleShape;

	Animation animation;

	bool faceRight = true; //Set whether to Face Right

private:


};


