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
	string type, string name, int itemId, int prince, string description, int hpChange, bool evoStone,int foodChange, int happinessChange, bool minigameLife, float xpCoupon)
	: GameObject(position, dimensions, originIsCenter, texturePath, imageCount, start, finish, frameTime) {
	
	this->type = type;
	this->name = name;
	this->itemId = itemId;
	this->price = price;				//this->{Tuaplae in class} = parameter;
	this->description = description;
	this->hpChange = hpChange;
	this->evoStone = evoStone;
	this->foodChange = foodChange;
	this->happinessChange = happinessChange;
	this->minigameLife = minigameLife;
	this->xpCoupon = xpCoupon;
}

Item::Item(Vector2f position, Vector2f dimensions, bool originIsCenter, string texturePath, Vector2u imageCount, Vector2i start, Vector2i finish, float frameTime,
	string name)
	: GameObject(position, dimensions, originIsCenter, texturePath, imageCount, start, finish, frameTime) {
	this->name = name;
	if (name == "cheeseCake")
	{
		type = "food";
		itemId = 1;
		price = 35;
		description = description;
		hpChange =-10;
		evoStone = false;
		foodChange = 20;
		happinessChange = 25;
		minigameLife = false;
		xpCoupon = 0.0;
	}
	else if (name=="honeyPeach")
	{
		type = "food";
		itemId = 2;
		price = 15;
		this->description = description;
		this->hpChange = 5;
		this->evoStone = false;
		this->foodChange = 15;
		this->happinessChange = -5;
		this->minigameLife = false;
		this->xpCoupon = 0.0;
	}
	else if (name=="milk")
	{
		type = "food";
		itemId = 3;
		this->price = 20;
		this->description = description;
		this->hpChange = 10;
		this->evoStone = false;
		this->foodChange = 15;
		this->happinessChange = 5;
		this->minigameLife = false;
		this->xpCoupon = 0.0;
	}
	else if (name=="noodle69")
	{
		type = "food";
		itemId = 4;
		this->price = 69;
		this->description = description;
		this->hpChange = 69;
		this->evoStone = false;
		this->foodChange = 69;
		this->happinessChange = 0;
		this->minigameLife = false;
		this->xpCoupon = 0.0;
	}
	else if (name=="icecream")
	{
		type = "food";
		itemId = 5;
		this->price = 5;
		this->description = description;
		this->hpChange = -5;
		this->evoStone = evoStone;
		this->foodChange = 15;
		this->happinessChange = 0;
		this->minigameLife = minigameLife;
		this->xpCoupon = xpCoupon;
	}
	else if (name=="honeyRoll")
	{
		type = "food";
		itemId = 6;
		this->price = 25;
		this->description = description;
		this->hpChange = 5;
		this->evoStone = false;
		this->foodChange = 30;
		this->happinessChange = 10;
		this->minigameLife = false;
		this->xpCoupon = 0.0;
	}
	else {
		type = "not Item";
		itemId = 10;
		this->price = 0;
		this->description = "Item not set";
		this->hpChange = hpChange;
		this->evoStone = false;
		this->foodChange = foodChange;
		this->happinessChange = happinessChange;
		this->minigameLife = minigameLife;
		this->xpCoupon = xpCoupon;
	};
	this->type = type;
	this->name = name;
	this->itemId = itemId;
	this->price = price;				//this->{Tuaplae in class} = parameter;
	this->description = description;
	this->hpChange = hpChange;
	this->evoStone = evoStone;
	this->foodChange = foodChange;
	this->happinessChange = happinessChange;
	this->minigameLife = minigameLife;
	this->xpCoupon = xpCoupon;
}
Item::~Item() {

}