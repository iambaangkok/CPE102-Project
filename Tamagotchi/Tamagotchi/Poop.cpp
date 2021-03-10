#include "Poop.h"

Poop::Poop(){
	nClickToDestroy = 3;
}

Poop::Poop(Vector2f position, Vector2f dimensions, bool originIsCenter,
	string texturePath, Vector2u imageCount, Vector2i start, Vector2i finish, float frameTime, int nClickToDestroy, float floorLine)
	: GameObject(position, dimensions, originIsCenter, texturePath, imageCount, start, finish, frameTime)
{
	this->nClickToDestroy = nClickToDestroy;
	this->floorLine = floorLine;
	price = rand() % priceRange + startingPrice;
}

Poop::~Poop(){}

void Poop::Initialize() {
}//Runs before everything else in every game loop/ reset variable that needs to be reset every game loop

void Poop::Update(float deltaTime, RenderWindow& window, unordered_map<string, bool>& mousePress, Vector2i& mousePosition) {
	if (!enabled) {
		return;
	}
	animation.Update(deltaTime);
	float poopSize = (basePoopSize - lowestPoopSize)/3 * nClickToDestroy + lowestPoopSize;

	if (GetPosition().y < floorLine) {
		speed.y += gravity * deltaTime;
		Move(speed.x * deltaTime, speed.y * deltaTime);
	}
	else {
		speed = Vector2f(0, 0);
		if (GetPosition().y > floorLine) {
			SetPosition(GetPosition().x, floorLine);
		}
	}

	drawLayer = GetSide("BOTTOM");

	if (faceRight) {
		rectangleShape.setScale(Vector2f(poopSize, poopSize));
	}
	else {
		rectangleShape.setScale(Vector2f(-poopSize, poopSize));
	}
	rectangleShape.setTextureRect(animation.uvRect);


	if (IsMouseOver(mousePosition) && mousePress["M1"]) {
		OnClick();
	}
	else if (IsMouseOver(mousePosition)) {
		OnHover();
	}
	else {

	}

}


void Poop::OnClick() {
	nClickToDestroy--;
}

void Poop::OnHover() {

}

bool Poop::IsMouseOver(Vector2i& mousePosition) {

	Vector2f posi = GetPosition();
	Vector2f dimen = GetDimensions();
	Vector2f a = Vector2f(posi.x - dimen.x / 2, posi.y - dimen.y / 2);
	Vector2f b = Vector2f(posi.x + dimen.x / 2, posi.y + dimen.y / 2);

	if (mousePosition.x > a.x && mousePosition.x < b.x && mousePosition.y > a.y && mousePosition.y < b.y) {
		return true;
	}
	return false;
}