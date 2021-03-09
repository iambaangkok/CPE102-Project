#include "Button.h"
#include "Game.h"
using std::cout;
using std::endl;
Button::Button() {

}

Button::Button(Vector2f position, Vector2f dimensions, bool originIsCenter,
    string texturePath, Vector2u imageCount, Vector2i start, Vector2i finish, float frameTime
    ,string text, int status, string type,int &gstate,Shop &shop,Pet &pet,int id)
    : GameObject(position, dimensions, originIsCenter, texturePath, imageCount, start, finish, frameTime)
{
    this->text = text;
    this->status = status;
    this->type = type;
	this->gstate = &gstate;
	this->shop = &shop;
	this->pet = &pet;
}
//Proper Animation

Button::~Button() {

}

void Button::Initialize() {
}//Runs before everything else in every game loop/ reset variable that needs to be reset every game loop

void Button::Update(float deltaTime,RenderWindow& window,unordered_map<string, bool>& mousePress, Vector2i& mousePosition, bool &quitGame) {
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


	
	if (IsMouseOver(mousePosition) && mousePress["M1"]) {
		OnClick(quitGame);
	}
	else if (IsMouseOver(mousePosition)) {
		OnHover();
	}
	else {
		status = 0;
	}

	if (type == "BUYITEM" && pet->money < shop->items[id - 1].price) status = 3;

	animation.SetFrame(Vector2i(status, 0));


}

void Button::OnClick(bool &quitGame) {
	status = 2;
	if (type == "MAIN") {
		*gstate = 1;
	}
	else if (type == "SHOP") {
		if (shop->isOpen == false) shop->isOpen = true;
		else shop->isOpen = false;
	}
	else if (type == "MINIGAME") {
		if (*gstate == 1) {
			*gstate = 2;
		}
		else {
			*gstate = 1;
		}
	}
	else if (type == "SETTING") {
		*gstate = 3;
	}
	if (type == "BUYITEM" && pet->money >= shop->items[id-1].price) {
		pet->money -= shop->items[id - 1].price;
		shop->items[id-1].UseItem(pet);
	}
	if (type == "EXIT") quitGame = true;
}

void Button::OnHover() {
	status = 1;
}


bool Button::IsMouseOver(Vector2i& mousePosition) {

	Vector2f posi = GetPosition();
	Vector2f dimen = GetDimensions();
	Vector2f a = Vector2f(posi.x, posi.y);
	Vector2f b = Vector2f(posi.x+dimen.x, posi.y+dimen.y);

	if (mousePosition.x > a.x && mousePosition.x < b.x && mousePosition.y > a.y && mousePosition.y < b.y) {
		return true;
	}
	return false;
}