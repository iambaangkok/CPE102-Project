#include "Button.h"
#include "Game.h"
using std::cout;
using std::endl;
Button::Button() {

}

Button::Button(Vector2f position, Vector2f dimensions, bool originIsCenter,
    string texturePath, Vector2u imageCount, Vector2i start, Vector2i finish, float frameTime
    ,string text, int status, string type,int &gstate,Shop &shop,Pet &pet,Doodle &doodle,int id)
    : GameObject(position, dimensions, originIsCenter, texturePath, imageCount, start, finish, frameTime)
{
    this->text = text;
    this->status = status;
    this->type = type;
	this->gstate = &gstate;
	this->shop = &shop;
	this->pet = &pet;
	this->doodle = &doodle;
	this->id = id;
	
}
//Proper Animation

Button::~Button() {

}

void Button::Initialize() {
}//Runs before everything else in every game loop/ reset variable that needs to be reset every game loop

void Button::Update(float deltaTime,RenderWindow& window,unordered_map<string, bool>& mousePress, unordered_map<string, bool>& mouseHold, Vector2i& mousePosition, bool &quitGame, int& selectedPet, bool& clearSave, bool& muteBgm, bool& muteSfx, Button& food, Button& candy , Button& etcc) {
	if (!enable) {
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
		OnClick(muteBgm,muteSfx,food,candy,etcc);
	}
	else if (IsMouseOver(mousePosition) && mouseHold["M1"]) {
		OnHold();
	}
	
	else if (IsMouseOver(mousePosition)) {
		OnHover();
	}
	else {
		if (text == "TOGGLE" && isPressed && !IsMouseOver(mousePosition)) status = 2;
		else if (text == "TOGGLE" && isPressed && IsMouseOver(mousePosition)) status = 3;
		else status = 0;
	}
	if (prevstatus == 3 && status == 1) OnRelease(quitGame, selectedPet, clearSave);
	prevstatus = status;

	if (type == "BUYITEM" && pet->money < shop->items[id - 1]->price) status = 4;
	if (type == "EVOLVE" && pet->currentExp < pet->expPerEvolve[pet->currentLevel] && pet->ateEvolveStone == false) status = 4;
	animation.SetFrame(Vector2i(status, 0));


}

void Button::OnClick(bool& muteBgm, bool& muteSfx, Button& food, Button& candy, Button& etcc) {
	status = 2;
	if (text == "TOGGLE") {
		if (isPressed == false) {
			isPressed = true;
			status = 3;
		}
		else{
			isPressed = false;
			status = 0;
		}
		if (type == "SHOP") {
			if (isPressed) {
				shop->isOpen = true;
			}
			else {
				shop->isOpen = false;
			}
		}
		if (type == "MAINDISH") {
			status = 3;
			candy.isPressed = false;
			etcc.isPressed = false;
			shop->status = "food";
		}
		if (type == "DESSERT") {
			status = 3;
			food.isPressed = false;
			etcc.isPressed = false;
			shop->status = "candy";
		}
		if (type == "ETC") {
			status = 3;
			food.isPressed = false;
			candy.isPressed = false;
			shop->status = "etc";
		}
		if (type == "MUTEBGM") {
			cout << "MUTEBGM";
			if (muteBgm == false) {
				muteBgm = true;
			}
			else {
				muteBgm = false;
			}
		}
		if (type == "MUTESFX") {
			cout << "MUTESFX";
			if (muteSfx == false) {
				muteSfx = true;
			}
			else {
				muteSfx = false;
			}
		}
	}
}

void Button::OnHover() {
	if (isPressed == false) status = 1;
	else status = 3;
}

void Button::OnHold() {
	status = 3;
}

void Button::OnRelease(bool& quitGame, int& selectedPet, bool& clearSave) {
	if(text != "TOGGLE") status = 0;
	if (type == "MAIN") {
		*gstate = 1;
	}
	if (type == "MINIGAME") {
		if (pet->isAlive == true) {
			if (*gstate == 1) {
				*gstate = 2;
			}
			else {
				*gstate = 1;
			}
		}
		else {
			status = 4;
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
	if (type == "PETEGG") {
		cout << "Pet ID = " << id << endl;
		selectedPet = id;
		*gstate = 1;
	}
	if (type == "STARTDOODLE") {
		doodle->gstate = 1;
		doodle->music.play();
		//doodle->sound.play();
	}
	if (type == "EXITDOODLE") {
		doodle->gstate = -1;
		doodle->pass = true;
		*gstate = 1;
	}
	if (type == "CHOOSEBG") {
		doodle->gstate = 3;
		//doodle->sound.play();
	}
	if (type == "LEFTDOODLE") {
		doodle->equip--;
	}
	if (type == "RIGHTDOODLE") {
		doodle->equip++;
	}
	if (type == "BACKDOODLE") {
		if (text == "DEFAULT") {
			doodle->gstate = 0;
			//doodle->pass = true;
			//doodle->sound.play();
		}
		if (text == "GAMEOVER") {
			doodle->music.stop();
			doodle->gstate = -1;
			pet->money += doodle->Money + doodle->MoneyPickup;
			doodle->pass = true;
			*gstate = 1;
		}
	}
	if (type == "SELECTBG") {
		if (doodle->unlocklvl[doodle->equip] <= doodle->highscore) {
			doodle->equipnow = doodle->equip;
			doodle->InitBG();
		}
		else {
			//doodle->sound.play();
		}
	}
	if (type == "RESET") {
		clearSave = true;
	}
	if (type == "EVOLVE") {
		if ( (pet->currentExp == pet->expPerEvolve[pet->currentLevel]) && pet->ateEvolveStone == true) {
			pet->ateEvolveStone = false;
			pet->currentExp = 0;
			pet->currentLevel += 1;
			if (pet->currentLevel >= 2) pet->currentLevel = 2;
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