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


	//void Update(float deltaTime); //Single Texture DEPRICATED
	void Initialize();
	void Update(int row, float deltaTime, bool faceRight); //1Row Animation, Single Texture from Texture Sheet
	void Update(Vector2i start, Vector2i finish, float deltaTime);//Proper Animation
	void Update(float deltaTime);//Proper Animation


	void Draw(RenderWindow& window);
	void Move(float speedX, float speedY);//Simple Move

	Vector2f GetPosition(); //Returns Origin position
	Vector2f GetSize(); //Returns Dimensions
	Vector2f GetDimensions(); //Same as GetSize()

	void SetPosition(Vector2f position); // Set Position
	void SetPosition(float x, float y);
	void SetDimensions(Vector2f dimensions); // Set dimension
	void SetDimensions(float x, float y);
	void SetOrigin(Vector2f origin); // Set origin
	void SetOrigin(float x, float y);
	void SetTexture(string texturePath); // Set texture
	void SetImageCount(Texture& texture, Vector2u imageCount); // Set image count
	void SetStartFrame(Vector2i start); // Set 1st Frame
	void SetStartFrame(int x, int y);
	void SetFinishFrame(Vector2i finish); // Set last frame
	void SetFinishFrame(int x, int y);
	void SetFrameTime(float frameTime); // Set frametime

	bool CheckCollision(GameObject &other , float push); //Check if 2 objects collide each other

	

	bool enabled = true; 

	Vector2f speed = Vector2f(0, 0);

	Texture texture;
	RectangleShape rectangleShape;

	Animation animation;

	bool faceRight = true; //Set whether to Face Right

	Vector2f direction; // Show what side of object that collide (Left , Right , Up , Down) Use in CheckCollision();

private:


};


