#include "Item.h"

Item::Item(){
	Vector2f dimensions = Vector2f(100, 100);
	Vector2f position = Vector2f(200, 200);
	string texturePath = "Assets/Textures/DefaultTexture.png";

	rectangleShape = RectangleShape(dimensions);
	rectangleShape.setPosition(position);
	rectangleShape.setOrigin(Vector2f(dimensions.x / 2, dimensions.y / 2));

	if (texture.loadFromFile(texturePath)) {
		cout << "Loaded Default Texture" << endl;
	}

	Vector2u textureSize = texture.getSize();
	rectangleShape.setTexture(&texture);
}

//Single Texture
Item::Item(Vector2f position, Vector2f dimensions, bool originIsCenter, string texturePath){

	rectangleShape = RectangleShape(dimensions);
	rectangleShape.setPosition(position);
	if (originIsCenter) {
		rectangleShape.setOrigin(Vector2f(dimensions.x / 2, dimensions.y / 2));
	}

	if (texture.loadFromFile(texturePath)) {
		cout << "Loaded " + texturePath << endl;
	}

	Vector2u textureSize = texture.getSize();
	rectangleShape.setTexture(&texture);
}

//1Row Animation from Texture Sheet
Item::Item(Vector2f position, Vector2f dimensions, bool originIsCenter, string texturePath, Vector2u imageCount, float frameTime) {

	rectangleShape = RectangleShape(dimensions);
	rectangleShape.setPosition(position);
	if (originIsCenter) {
		rectangleShape.setOrigin(Vector2f(dimensions.x / 2, dimensions.y / 2));
	}

	if (texture.loadFromFile(texturePath)) {
		cout << "Loaded " + texturePath << endl;
	}
	rectangleShape.setTexture(&texture);

	animation = Animation(&texture, imageCount, frameTime);
}

//Single Texture from Texture Sheet
Item::Item(Vector2f position, Vector2f dimensions, bool originIsCenter, string texturePath, Vector2u imageCount, Vector2i imageCoordinate) {
	cout << "Con3" << endl;
	rectangleShape = RectangleShape(dimensions);
	rectangleShape.setPosition(position);
	rectangleShape.setSize(dimensions);
	if (originIsCenter) {
		rectangleShape.setOrigin(Vector2f(dimensions.x / 2, dimensions.y / 2));
	}


	if (texture.loadFromFile(texturePath)) {
		cout << "Loaded " + texturePath << endl;
	}

	rectangleShape.setTexture(&texture);

	animation = Animation(&texture, imageCount);
	animation.freezeFrame = true;
	animation.SetFrame(imageCoordinate);
}

//Proper Animation
Item::Item(Vector2f position, Vector2f dimensions, bool originIsCenter, string texturePath, Vector2u imageCount, Vector2i start, Vector2i finish, float frameTime) {
	cout << "Con4" << endl;
	rectangleShape = RectangleShape(dimensions);
	rectangleShape.setPosition(position);
	rectangleShape.setSize(dimensions);
	if (originIsCenter) {
		rectangleShape.setOrigin(Vector2f(dimensions.x / 2, dimensions.y / 2));
	}


	if (texture.loadFromFile(texturePath)) {
		cout << "Loaded " + texturePath << endl;
	}
	rectangleShape.setTexture(&texture);
	animation = Animation(&texture, imageCount, frameTime);
	animation.SetStartFrame(start);
	animation.SetFinishFrame(finish);
	animation.SetFrame(start);
}

//Item in shop
Item::Item(Vector2f position, Vector2f dimensions, bool originIsCenter, string texturePath, Vector2u imageCount, Vector2i start, Vector2i finish, float frameTime,
	string name, string description, int hpChange, bool evoStone, int foodChange, int happinessChange, bool minigameLife, float xpCoupon)
	: GameObject(position, dimensions, originIsCenter, texturePath, imageCount, start, finish, frameTime) {
	
	
	this->name = name;					//this->{Tuaplae in class} = parameter;
	this->description = description;
	this->evoStone = evoStone;
	this->foodChange = foodChange;
	this->happinessChange = happinessChange;
	this->minigameLife = minigameLife;
	this->xpCoupon = xpCoupon;
}

Item::~Item() {

}