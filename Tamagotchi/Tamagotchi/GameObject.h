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

	void SetPosition(Vector2f position); // Set Position
	void SetDimensions(Vector2f dimensions); // Set dimension
	void SetOrigin(Vector2f origin); // Set origin
	void SetTexture(string texturePath); // Set texture
	void SetImageCount(Texture& texture, Vector2u imageCount); // Set image count
	void SetStartFrame(Vector2i start); // Set 1st Frame
	void SetFinishFrame(Vector2i finish); // Set last frame
	void SetFrameTime(float frameTime); // Set frametime

	bool CheckCollision(GameObject &other ,Vector2f & direction, float push); //Check if 2 objects collide each other


	bool enabled = true; 

	Texture texture;
	RectangleShape rectangleShape;

	Animation animation;

	bool faceRight = true; //Set whether to Face Right

	Vector2f direction; // Show what side of object that collide (Left , Right , Up , Down);

private:


};


