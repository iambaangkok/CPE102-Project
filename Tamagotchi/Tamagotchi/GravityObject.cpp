#include "GravityObject.h"


GravityObject::GravityObject(Vector2f position, Vector2f dimensions, float Height, string filepath)
{
	playertexture.loadFromFile(filepath);
	player.SetPosition(position);
	player.SetDimensions(dimensions);
	player.SetOrigin(dimensions / 2.0f);
	
	player.rectangleShape.setTexture(&playertexture, true);
	player.animation = Animation(&playertexture, Vector2u(5, 3), 0.0f);
	player.animation.freezeFrame = true;
	player.animation.SetFrame(Vector2i(0, 0));
	player.rectangleShape.setTextureRect(player.animation.uvRect);
	
	this->Height = Height;
	this->playerX = position.x;
	this->playerY = position.y;
}

GravityObject::~GravityObject()
{

}

void GravityObject::Update(float deltaTime , float speed_rate , int curlevel)
{	
	if (Keyboard::isKeyPressed(Keyboard::Left))
		playerX -= 800.0f * deltaTime * (1.0f - speed_rate);
	if (Keyboard::isKeyPressed(Keyboard::Right))
		playerX += 800.0f * deltaTime * (1.0f - speed_rate);
	if (playerX > 720)
		playerX = 720;
	if (playerX < 0)
		playerX = 0;

	if (dy < -300.0f)
		player.animation.SetFrame(Vector2i(3, curlevel));
	else if (dy > 200.0f)
		player.animation.SetFrame(Vector2i(4, curlevel));
	else
		player.animation.SetFrame(Vector2i(0, curlevel));

	player.SetPosition(Vector2f(playerX, playerY));
	player.rectangleShape.setTextureRect(player.animation.uvRect);
}

bool GravityObject::CheckCollision(Vector2f otherPos, Vector2f otherHalfSize)
{
	Vector2f thisPos = player.GetPosition();
	Vector2f thisHalfSize = player.GetSize() / 2.0f;

	float deltaX = otherPos.x - thisPos.x;
	float deltaY = otherPos.y - thisPos.y;

	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if (intersectX < 0.0f && intersectY < 0.0f) {
		if (intersectX > intersectY) {
			if (deltaX > 0.0f) {

			}
			else {

			}
		}
		else {
			if (deltaY > 0.0f) {
				return true;
			}
			else {

			}
		}
	}
	return false;
}
