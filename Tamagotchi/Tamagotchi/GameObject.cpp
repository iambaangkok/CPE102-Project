#include "GameObject.h"

GameObject::GameObject() {

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

void GameObject::Update(float deltaTime) {
	if (!enabled) {
		return;
	}
	rectangleShape.setTexture(&texture);
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

Vector2f GameObject::GetPosition() {
	return rectangleShape.getPosition();
}

Vector2f GameObject::GetSize()
{
	return rectangleShape.getSize();
}

void GameObject::checkCollision(GameObject &other , float push)
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
			}
			else {
				Move(-intersectX * (1.0f - push), 0.0f);
				other.Move(intersectX * push, 0.0f);
			}
		}
		else {
			if (deltaY > 0) {
				Move(0.0f, intersectY * (1.0f - push));
				other.Move(0.0f, -intersectY * push);
			}
			else {
				Move(0.0f, -intersectY * (1.0f - push));
				other.Move(0.0f, intersectY * push);
			}
		}
	}
}
