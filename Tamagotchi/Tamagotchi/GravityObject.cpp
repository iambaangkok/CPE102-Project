#include "GravityObject.h"

GravityObject::GravityObject(Vector2f position, Vector2f dimensions, bool originIsCenter, float speed, float jumpHeight)
{
	rectangleShape = RectangleShape(dimensions);
	rectangleShape.setPosition(position);
	if (originIsCenter) {
		rectangleShape.setOrigin(Vector2f(dimensions.x / 2, dimensions.y / 2));
	}
	rectangleShape.setFillColor(Color::White);
	this->speed = speed;
	this->jumpHeight = jumpHeight;

}

GravityObject::~GravityObject()
{

}

void GravityObject::Update(float deltaTime)
{
	velocity.x = 0.0f;
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		velocity.x -= speed;
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		velocity.x += speed;
	}
	if (Keyboard::isKeyPressed(Keyboard::Space) && canJump) {
		canJump = false;
		velocity.y -= sqrt(2.0f * 981.0f * jumpHeight);
	}
	velocity.y += 981.0f * deltaTime;
	cout << velocity.x << " " << velocity.y <<endl;
	Move(velocity.x * deltaTime , velocity.y * deltaTime);
}

void GravityObject::OnCollision(Vector2f direction)
{
	if (velocity.y < 0)
		return;
	if (direction.x < 0.0f) {
		velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f) {
		velocity.x = 0.0f;
	}
	if (direction.y < 0.0f) {
		velocity.y = 0.0f;
		canJump = true;
	}
	else if(direction.y > 0.0f){
		velocity.y = 0.0f;
	}
}
