#include "GameObject.h"

//Default
GameObject::GameObject() {
	Vector2f dimensions = Vector2f(100, 100);
	Vector2f position = Vector2f(200, 200);
	string texturePath = "Assets/Textures/DefaultTexture.png";

	rectangleShape = RectangleShape(dimensions);
	rectangleShape.setPosition(position);
	rectangleShape.setOrigin(Vector2f(dimensions.x / 2, dimensions.y / 2));

	if (texture.loadFromFile(texturePath)) {
		cout << "Loaded Default Texture" << endl;
	}

	Vector2u textureSize = texture.getSize();
	rectangleShape.setTexture(&texture);
}

//Fill Color
GameObject::GameObject(Vector2f position, Vector2f dimensions, bool originIsCenter, Color color) {

	rectangleShape = RectangleShape(dimensions);
	rectangleShape.setPosition(position);
	this->originIsCenter = originIsCenter;
	if (originIsCenter) {
		rectangleShape.setOrigin(Vector2f(dimensions.x / 2, dimensions.y / 2));
	}

	rectangleShape.setFillColor(color);
	IsUpdateAnimation = false;
	
}

//Single Texture
GameObject::GameObject(Vector2f position, Vector2f dimensions, bool originIsCenter, string texturePath) {

	rectangleShape = RectangleShape(dimensions);
	rectangleShape.setPosition(position);
	if (originIsCenter) {
		rectangleShape.setOrigin(Vector2f(dimensions.x / 2, dimensions.y / 2));
	}

	if (texture.loadFromFile(texturePath)) {
		filepath = texturePath;
		cout << "Loaded " + texturePath << endl;
	}
	
	Vector2u textureSize = texture.getSize();
	rectangleShape.setTexture(&texture);
}

//1Row Animation from Texture Sheet
GameObject::GameObject(Vector2f position, Vector2f dimensions, bool originIsCenter, string texturePath, Vector2u imageCount, float frameTime){ 

	rectangleShape = RectangleShape(dimensions);
	rectangleShape.setPosition(position);
	if (originIsCenter) {
		rectangleShape.setOrigin(Vector2f(dimensions.x / 2, dimensions.y / 2));
	}

	if (texture.loadFromFile(texturePath)) {
		filepath = texturePath;
		cout << "Loaded " + texturePath << endl;
	}
	rectangleShape.setTexture(&texture);

	animation = Animation(&texture, imageCount, frameTime);
}

//Single Texture from Texture Sheet
GameObject::GameObject(Vector2f position, Vector2f dimensions, bool originIsCenter, string texturePath, Vector2u imageCount, Vector2i imageCoordinate){ 
	cout << "Con3" << endl;
	rectangleShape = RectangleShape(dimensions);
	rectangleShape.setPosition(position);
	rectangleShape.setSize(dimensions);
	if (originIsCenter) {
		rectangleShape.setOrigin(Vector2f(dimensions.x / 2, dimensions.y / 2));
	}

	
	if (texture.loadFromFile(texturePath)) {
		filepath = texturePath;
		cout << "Loaded " + texturePath << endl;
	}

	rectangleShape.setTexture(&texture);

	animation = Animation(&texture, imageCount);
	animation.freezeFrame = true;
	animation.SetFrame(imageCoordinate);
}

//Proper Animation
GameObject::GameObject(Vector2f position, Vector2f dimensions, bool originIsCenter, string texturePath, Vector2u imageCount, Vector2i start, Vector2i finish,float frameTime) { 
	cout << "Con4" << endl;
	rectangleShape = RectangleShape(dimensions);
	rectangleShape.setPosition(position);
	rectangleShape.setSize(dimensions);
	this->originIsCenter = originIsCenter;
	if (originIsCenter) {
		rectangleShape.setOrigin(Vector2f(dimensions.x / 2, dimensions.y / 2));
	}
	rectangleShape.setRotation(0);

	if (texture.loadFromFile(texturePath)) {
		filepath = texturePath;
		cout << "Loaded " + texturePath << endl;
	}
	rectangleShape.setTexture(&texture);
	animation = Animation(&texture, imageCount, frameTime);
	animation.SetStartFrame(start);
	animation.SetFinishFrame(finish);
	animation.SetFrame(start);
}

GameObject::~GameObject() {

}

void GameObject::Initialize() {
	speed = Vector2f(0, 0);
}

void GameObject::Update(float deltaTime) { // Proper Animation
	if (!enabled) {
		return;
	}
	if (IsUpdateAnimation) {
		animation.Update(deltaTime);
		if (faceRight) {
			rectangleShape.setScale(Vector2f(1, 1));
		}
		else {
			rectangleShape.setScale(Vector2f(-1, 1));
		}
		rectangleShape.setTextureRect(animation.uvRect);
	}
	
	Move(speed.x * deltaTime, speed.y * deltaTime);
	//rectangleShape.setTexture(&texture);
}

void GameObject::Update(int row, float deltaTime,bool faceRight) {
	if (!enabled) {
		return;
	}
	animation.Update(row, deltaTime, faceRight);
	rectangleShape.setTextureRect(animation.uvRect);
}

void GameObject::Update(Vector2i start, Vector2i finish, float deltaTime) {
	if (!enabled) {
		return;
	}
	animation.Update(start, finish, deltaTime);

	if (faceRight) {
		rectangleShape.setScale(Vector2f(1, 1));
	}
	else {
		rectangleShape.setScale(Vector2f(-1, 1));
	}
	rectangleShape.setTextureRect(animation.uvRect);
}

void GameObject::Draw(RenderWindow& window) {
	window.draw(rectangleShape);
}
void GameObject::Move(float speedX, float speedY) {
	rectangleShape.move(speedX, speedY);
}
void GameObject::Rotate(float angle) {
	rectangleShape.rotate(angle);
}


int GameObject::CheckCollision(Vector2f otherPos, Vector2f otherHalfSize)
{
	Vector2f thisPos = GetPosition();
	Vector2f thisHalfSize = GetSize() / 2.0f;

	float deltaX = otherPos.x - thisPos.x;
	float deltaY = otherPos.y - thisPos.y;

	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	/*
		state :
			0 - Pet doesn't hit object.
			1 - The right side of pet hit object.
			2 - The left side of pet hit object.
			3 - The bottom side of pet hit object.
			4 - The top side of pet hit object.
	*/

	if (intersectX < 0.0f && intersectY < 0.0f) {
		if (intersectX > intersectY) {
			if (deltaX > 0.0f)
				return 1;
			else
				return 2;
		}
		else {
			if (deltaY > 0.0f)
				return 3;
			else
				return 4;
		}
	}
	return 0;
}
int GameObject::CheckCollision(GameObject& other) {
	Vector2f thisPos = GetPosition();
	Vector2f thisHalfSize = GetSize() / 2.0f;
	Vector2f otherPos = other.GetPosition();
	Vector2f otherHalfSize = other.GetDimensions() / 2.0f;

	float deltaX = otherPos.x - thisPos.x;
	float deltaY = otherPos.y - thisPos.y;

	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	/*
		state :
			0 - Pet doesn't hit object.
			1 - The right side of pet hit object.
			2 - The left side of pet hit object.
			3 - The bottom side of pet hit object.
			4 - The top side of pet hit object.
	*/

	if (intersectX < 0.0f && intersectY < 0.0f) {
		if (intersectX > intersectY) {
			if (deltaX > 0.0f)
				return 1;
			else
				return 2;
		}
		else {
			if (deltaY > 0.0f)
				return 3;
			else
				return 4;
		}
	}
	return 0;
}


Vector2f GameObject::GetPosition() {
	return rectangleShape.getPosition();
}
Vector2f GameObject::GetSize()
{
	return rectangleShape.getSize();
}
Vector2f GameObject::GetDimensions()
{
	return rectangleShape.getSize();
}
float GameObject::GetRotation() {
	return rectangleShape.getRotation();
}
Color GameObject::GetColor() {
	return rectangleShape.getFillColor();
}
float GameObject::GetSide(string side) {
	Vector2f pos = GetPosition();
	Vector2f dim = GetDimensions();
	if (originIsCenter) {
		dim = Vector2f(dim.x / 2, dim.y / 2);
		if (side == "LEFT") {
			return pos.x - dim.x;
		}
		else if (side == "RIGHT") {
			return pos.x + dim.x;
		}
		else if (side == "TOP") {
			return pos.y - dim.y;
		}
		else if (side == "BOTTOM") {
			return pos.y + dim.y;
		}
	}
	else {
		if (side == "LEFT") {
			return pos.x;
		}
		else if (side == "RIGHT") {
			return pos.x + dim.x;
		}
		else if (side == "TOP") {
			return pos.y;
		}
		else if (side == "BOTTOM") {
			return pos.y + dim.y;
		}
	}
	return -1;
	
}


void GameObject::SetPosition(Vector2f position) // Set Position
{
	rectangleShape.setPosition(position);
}
void GameObject::SetPosition(float x, float y)
{
	rectangleShape.setPosition(Vector2f(x,y));
}
void GameObject::SetDimensions(Vector2f dimensions) // Set dimension
{
	rectangleShape.setSize(dimensions);
}
void GameObject::SetDimensions(float x, float y) 
{
	rectangleShape.setSize(Vector2f(x, y));
}
void GameObject::SetRotation(float angle) {
	rectangleShape.setRotation(angle);
}
void GameObject::SetOrigin(Vector2f origin) // Set origin
{
	rectangleShape.setOrigin(origin);
}
void GameObject::SetOrigin(float x, float y)
{
	rectangleShape.setOrigin(Vector2f(x, y));
}
void GameObject::SetTexture(string texturePath) // Set texture
{
	texture.loadFromFile(texturePath);
	rectangleShape.setTexture(&texture , true);
}
void GameObject::SetImageCount(Texture& texture,Vector2u imageCount) // Set image count
{
	animation.SetImageCount(texture,imageCount);  
}
void GameObject::SetStartFrame(Vector2i start) // Set 1st Frame
{
	animation.SetStartFrame(start);
}
void GameObject::SetStartFrame(int x, int y)
{
	animation.SetStartFrame(Vector2i(x, y));
}
void GameObject::SetFinishFrame(Vector2i finish) // Set last frame
{
	animation.SetFinishFrame(finish);
}
void GameObject::SetFinishFrame(int x, int y)
{
	animation.SetFinishFrame(Vector2i(x, y));
}
void GameObject::SetFrameTime(float frameTime) // Set frametime
{
	animation.SetFrameTime(frameTime);
}
void GameObject::SetStartFinishFrame(int sx, int sy, int fx, int fy) {
	animation.SetStartFinishFrame(sx, sy, fx, fy);
}
void GameObject::SetFrame(Vector2i imageCoordinate) {
	animation.SetFrame(imageCoordinate);
}
void GameObject::SetFrame(int x, int y) {
	animation.SetFrame(x, y);
}
void GameObject::SetColor(Color color) 
{
	rectangleShape.setFillColor(color);
}

//bool GameObject::CompareDrawLayer(const GameObject& x, const GameObject& y) {
//	return x.drawLayer < y.drawLayer;
//}
