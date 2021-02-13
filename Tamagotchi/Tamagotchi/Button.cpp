#include "Button.h"

Button::Button() {

}

Button::Button(Vector2f position, Vector2f dimensions, bool originIsCenter,
    string texturePath, Vector2u imageCount, Vector2i start, Vector2i finish, float frameTime
    , vector<Color> color, string text, int status, string type)
    : GameObject(position, dimensions, originIsCenter, texturePath, imageCount, start, finish, frameTime)
{
    this->color = color;
    this->text = text;
    this->status = status;
    this->type = type;
}
//Proper Animation

Button::~Button() {

}

void Button::Initialize() {

}//Runs before everything else in every game loop/ reset variable that needs to be reset every game loop

void Button::Update(float deltaTime,RenderWindow window) {
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
	//rectangleShape.setTexture(&texture);
	Vector2i mousePos = Mouse::getPosition(window);
	Vector2f posi = GetPosition();
	Vector2f dimen = GetDimensions();
	float x1 = posi.x - dimen.x / 2;
	float y1 = posi.y - dimen.y / 2;
	Vector2f a = Vector2f(x1,y1);
	float x2 = posi.x + dimen.x / 2;
	float y2 = posi.y + dimen.y / 2;
	Vector2f b = Vector2f(x2, y2);
	

}