#include "GravityObject.h"


GravityObject::GravityObject(Vector2f position, Vector2f dimensions, float Height, string filepath)
{
	playertexture.loadFromFile(filepath);
	player.rectangleShape.setTexture(&playertexture, true);
	player.SetPosition(position);
	player.SetDimensions(dimensions);
	
	player.SetOrigin(dimensions / 2.0f);
	

	this->Height = Height;
	this->playerX = position.x;
	this->playerY = position.y;
}

GravityObject::~GravityObject()
{

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
