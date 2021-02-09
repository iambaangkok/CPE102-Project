#include "GameObject.h"

GameObject::GameObject(Vector2f position, Vector2f dimensions, bool originIsCenter, String texturePath) {

	rectangleShape.setPosition(position);
	rectangleShape.setSize(dimensions);
	rectangleShape.setOrigin(Vector2f(dimensions.x/2,dimensions.y/2));

	texture.loadFromFile(texturePath);
	
	Vector2u textureSize = texture.getSize();
	rectangleShape.setTexture(&texture);
}

GameObject::GameObject(Vector2f position, Vector2f dimensions, bool originIsCenter, String texturePath, Vector2u imageCount, float frameTime){ //Animation from Texture Sheet

	rectangleShape.setPosition(position);
	rectangleShape.setSize(dimensions);
	rectangleShape.setOrigin(Vector2f(dimensions.x / 2, dimensions.y / 2));

	texture.loadFromFile(texturePath);

	Vector2u textureSize = texture.getSize();
	animation = Animation(&texture, imageCount, frameTime);

	rectangleShape.setTextureRect(animation.uvRect);
}

GameObject::GameObject(Vector2f position, Vector2f dimensions, bool originIsCenter, String texturePath, Vector2u imageCount, float frameTime, Vector2u uv){ //Single Texture from Texture Sheet

	rectangleShape.setPosition(position);
	rectangleShape.setSize(dimensions);
	rectangleShape.setOrigin(Vector2f(dimensions.x / 2, dimensions.y / 2));

	texture.loadFromFile(texturePath);

	Vector2u textureSize = texture.getSize();
	animation = Animation(&texture, imageCount, frameTime);

	rectangleShape.setTextureRect(animation.uvRect);
}

GameObject::~GameObject() {

}

void GameObject::Update(float deltaTime) {
	if (!enabled) {
		return;
	}
}
void GameObject::Draw(RenderWindow window) {
	window.draw(rectangleShape);
}
Vector2f GameObject::GetPosition() {
	return rectangleShape.getPosition();
}