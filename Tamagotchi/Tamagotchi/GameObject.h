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
		Color color); //Fill Color
	GameObject(Vector2f position, Vector2f dimensions, bool originIsCenter, 
		string texturePath = "Assets/Textures/DefaultTexture.png"); //Single Texture
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
	void Rotate(float angle);//Simple rotation, angle+ : clockwise, origin calculated from origin

	int CheckCollision(Vector2f otherPos, Vector2f otherHalfSize);
	int CheckCollision(GameObject& other);


	Vector2f GetPosition(); //Returns Origin position
	Vector2f GetSize(); //Returns Dimensions
	Vector2f GetDimensions(); //Same as GetSize()
	float GetRotation();//Returns rotation in degrees
	Color GetColor();//Returns rectangleShape's Color
	float GetSide(string side);//Returns x OR y coordinate of left/right/top/bottom

	void SetPosition(Vector2f position); // Set Position
	void SetPosition(float x, float y);
	void SetDimensions(Vector2f dimensions); // Set dimension
	void SetDimensions(float x, float y);
	void SetRotation(float angle);//angle+ : clockwise, origin calculated from origin
	void SetOrigin(Vector2f origin); // Set origin
	void SetOrigin(float x, float y);
	void SetTexture(string texturePath); // Set texture
	void SetImageCount(Texture& texture, Vector2u imageCount); // Set image count
	void SetStartFrame(Vector2i start); // Set 1st Frame
	void SetStartFrame(int x, int y);
	void SetFinishFrame(Vector2i finish); // Set last frame
	void SetFinishFrame(int x, int y);
	void SetStartFinishFrame(int sx, int sy, int fx, int fy);
	void SetFrameTime(float frameTime); // Set frametime
	void SetFrame(Vector2i imageCoordinate);
	void SetFrame(int x, int y);
	void SetColor(Color color); // Set Color

	//bool CompareDrawLayer(const GameObject& x, const GameObject& y);
	/*bool operator<(const GameObject& y) const {
		return drawLayer < y.drawLayer;
	}
	bool operator>(const GameObject& y) const {
		return drawLayer > y.drawLayer;
	}*/

	string filepath; 

	bool enabled = true; 
	bool IsUpdateAnimation = true;

	Vector2f speed = Vector2f(0, 0);

	Texture texture;
	RectangleShape rectangleShape;
	bool originIsCenter = false;

	Animation animation;

	int drawLayer = 1; //1 is drawnFirst

	bool faceRight = true; //Set whether to Face Right

	

private:


};


