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

	soundBuffers = vector<SoundBuffer>(sfxVariables.size(), SoundBuffer());
	for (int i = 0; i < sfxVariables.size(); ++i) {
		if (soundBuffers[i].loadFromFile(sfxVariables[i].filePath)) {
			cout << "Loaded SFX " << sfxVariables[i].filePath << endl;
		}
		else {
			cout << "Failed to load SFX " << sfxVariables[i].filePath << endl;
		}
		sfx.push_back(Sound(soundBuffers[i]));
		sfx[i].setVolume(sfxVariables[i].volume);
	}
}

Poop::~Poop(){}

void Poop::Initialize() {
}//Runs before everything else in every game loop/ reset variable that needs to be reset every game loop

bool Poop::Update(float deltaTime, RenderWindow& window, unordered_map<string, bool>& mousePress, Vector2i& mousePosition) {
	if (!enabled) {
		return false;
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
		return true;
	}
	else if (IsMouseOver(mousePosition)) {
		OnHover();
	}
	return false;
}


void Poop::OnClick() {
	nClickToDestroy--;
	sfx[0].play();
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