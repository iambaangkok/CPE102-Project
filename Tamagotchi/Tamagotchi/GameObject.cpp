#include "GameObject.h"



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

GameObject::GameObject(Vector2f position, Vector2f dimensions, bool originIsCenter, string texturePath, Vector2u imageCount, float frameTime){ //Animation from Texture Sheet

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

//GameObject::GameObject(Vector2f position, Vector2f dimensions, bool originIsCenter, string texturePath, Vector2u imageCount, float frameTime, Vector2u uv){ //Single Texture from Texture Sheet
//	cout << "Con3 ";
//	rectangleShape = RectangleShape(dimensions);
//	rectangleShape.setPosition(position);
//	rectangleShape.setSize(dimensions);
//	if (originIsCenter) {
//		rectangleShape.setOrigin(Vector2f(dimensions.x / 2, dimensions.y / 2));
//	}
//
//	if (texture.loadFromFile(texturePath)) {
//		cout << "Loaded " + texturePath << endl;
//	}
//	rectangleShape.setTexture(&texture);
//
//	animation = Animation(&texture, imageCount, frameTime);
//	animation.freezeFrame = true;
//	animation.SetFrame(uv);
//}

GameObject::~GameObject() {

}

void GameObject::Update(float deltaTime) {
	if (!enabled) {
		return;
	}
	rectangleShape.setTexture(&texture);
}

void GameObject::Update(int row, float deltaTime, bool faceRight) {
	if (!enabled) {
		return;
	}
	animation.Update(row, deltaTime, faceRight);
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