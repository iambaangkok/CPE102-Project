#include "GameObject.h"

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

//Single Texture
GameObject::GameObject(Vector2f position, Vector2f dimensions, bool originIsCenter, string texturePath) {

	rectangleShape = RectangleShape(dimensions);
	rectangleShape.setPosition(position);
	if (originIsCenter) {
		rectangleShape.setOrigin(Vector2f(dimensions.x / 2, dimensions.y / 2));
	}

	if (texture.loadFromFile(texturePath)) {
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
	if (originIsCenter) {
		rectangleShape.setOrigin(Vector2f(dimensions.x / 2, dimensions.y / 2));
	}


	if (texture.loadFromFile(texturePath)) {
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

void GameObject::Update(float deltaTime) { // Proper Animation
	if (!enabled) {
		return;
	}
	animation.Update(deltaTime);
	if (faceRight) {
		rectangleShape.setScale(Vector2f(1, 1));
	}
	else {
		rectangleShape.setScale(Vector2f(-1, 1));
	}
	rectangleShape.setTextureRect(animation.uvRect);
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

template<typename T>
void GameObject::Clamp(T& clampVariable, T upperClamp, T lowerClamp)
{
	if (clampVariable > upperClamp) clampVariable = upperClamp;
	if (clampVariable < lowerClamp) clampVariable = lowerClamp;
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

void GameObject::SetPosition(Vector2f position) // Set Position
{
	rectangleShape.setPosition(position);
}
void GameObject::SetDimensions(Vector2f dimensions) // Set dimension
{
	rectangleShape.setSize(dimensions);

}
void GameObject::SetOrigin(Vector2f origin) // Set origin
{
	rectangleShape.setOrigin(origin);
}
void GameObject::SetTexture(string texturePath) // Set texture
{
	rectangleShape.setTexture(&texture);
}
void GameObject::SetImageCount(Texture& texture,Vector2u imageCount) // Set image count
{
	animation.SetImageCount(texture,imageCount);  
}
void GameObject::SetStartFrame(Vector2i start) // Set 1st Frame
{
	animation.SetStartFrame(start);
}
void GameObject::SetFinishFrame(Vector2i finish) // Set last frame
{
	animation.SetFinishFrame(finish);
}
void GameObject::SetFrameTime(float frameTime) // Set frametime
{
	animation.SetFrameTime(frameTime);
}

bool GameObject::CheckCollision(GameObject& other, Vector2f& direction , float push)
{

	Vector2f otherPosition = other.GetPosition();
	Vector2f otherHalfSize = other.GetSize() / 2.0f;
	Vector2f thisPosition = GetPosition();
	Vector2f thisHalfSize = GetSize() / 2.0f;

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;

	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);
	/*cout << deltaX << " " << deltaY << endl;*/
	cout << intersectX << " " << intersectY << endl;

	if (intersectX < 0.0f && intersectY < 0.0f) {
		push = std::min(std::max(push, 0.0f), 1.0f);
		if (intersectX > intersectY) {
			if (deltaX > 0) {
				Move(intersectX * (1.0f - push), 0.0f);
				other.Move(-intersectX * push, 0.0f);
				direction.x = 1.0f;
				direction.y = 0.0f;
			}
			else {
				Move(-intersectX * (1.0f - push), 0.0f);
				other.Move(intersectX * push, 0.0f);
				direction.x = -1.0f;
				direction.y = 0.0f;
			}
		}
		else {
			if (deltaY > 0) {
				Move(0.0f, intersectY * (1.0f - push));
				other.Move(0.0f, -intersectY * push);
				direction.x = 0.0f;
				direction.y = 1.0f;
			}
			else {
				Move(0.0f, -intersectY * (1.0f - push));
				other.Move(0.0f, intersectY * push);
				direction.x = 0.0f;
				direction.y = -1.0f;
			}
		}
		return true;
	}
	return false;
}