#include "Button.h"
#include "Game.h"
using std::cout;
using std::endl;
Button::Button() {

}

Button::Button(Vector2f position, Vector2f dimensions, bool originIsCenter,
    string texturePath, Vector2u imageCount, Vector2i start, Vector2i finish, float frameTime
    ,string text, int status, string type,int &gstate,Shop &shop,Pet &pet,Doodle &doodle,Game &game,int id)
    : GameObject(position, dimensions, originIsCenter, texturePath, imageCount, start, finish, frameTime)
{
    this->text = text;
    this->status = status;
    this->type = type;
	this->gstate = &gstate;
	this->shop = &shop;
	this->pet = &pet;
	this->doodle = &doodle;
	this->game = &game;
	this->id = id;
	
}
//Proper Animation

Button::~Button() {

}

void Button::Initialize() {
}//Runs before everything else in every game loop/ reset variable that needs to be reset every game loop

void Button::Update(float deltaTime,RenderWindow& window,unordered_map<string, bool>& mousePress, unordered_map<string, bool>& mouseHold, Vector2i& mousePosition, bool &quitGame, int& selectedPet) {
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


	
	if (IsMouseOver(mousePosition) && mouseHold["M1"]) {
		OnHold();
	}
	else if (IsMouseOver(mousePosition)) {
		OnHover();
	}
	else if (IsMouseOver(mousePosition) && mousePress["M1"]) {
		OnClick();
	}
	else {
		status = 0;
	}
	if (prevstatus == 3 && status == 1) OnRelease(quitGame, selectedPet);
	cout << prevstatus << " " << status << endl;
	prevstatus = status;

	if (type == "BUYITEM" && pet->money < shop->items[id - 1]->price) status = 4;

	animation.SetFrame(Vector2i(status, 0));


}

void Button::OnClick() {
	status = 2;
}

void Button::OnHover() {
	status = 1;
}

void Button::OnHold() {
	status = 3;
}

void Button::OnRelease(bool& quitGame, int& selectedPet) {
	status = 0;
	if (type == "MAIN") {
		*gstate = 1;
	}
	if (type == "SHOP") {
		if (shop->isOpen == false) shop->isOpen = true;
		else shop->isOpen = false;
	}
	if (type == "MINIGAME") {
		if (*gstate == 1) {
			*gstate = 2;
		}
		else {
			*gstate = 1;
		}
	}
	if (type == "SETTING") {
		*gstate = 3;
	}
	if (type == "BUYITEM" && pet->money >= shop->items[id - 1]->price) {
		pet->money -= shop->items[id - 1]->price;
		shop->items[id - 1]->UseItem(pet);
	}
	if (type == "EXIT") quitGame = true;
	if (type == "MAINDISH") {
		
	}
	if (type == "DESSERT") {

	}
	if (type == "ETC") {

	}
	if (type == "PETEGG") {
		cout << "Pet ID = " << id << endl;
		selectedPet = id;
		*gstate = 1;
	}
	if (type == "STARTDOODLE") {
		doodle->gstate = 1;
	}
	if (type == "EXITDOODLE") {
		doodle->gstate = -1;
		*gstate = 1;
	}
	if (type == "CHOOSEBG") {
		doodle->gstate = 3;
	}
	if (type == "LEFTDOODLE") {
		doodle->equip--;
	}
	if (type == "RIGHTDOODLE") {
		doodle->equip++;
	}
	if (type == "BACKDOODLE") {
		doodle->gstate = 0;
	}
	if (type == "SELECTBG") {
		doodle->InitBG();
	}
	if (type == "RESET") {
		game->ClearSave();
	}
	if (type == "MUTE") {
		if (text == "BGM") {

		}
		else if (text == "SFX") {

		}
	}
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