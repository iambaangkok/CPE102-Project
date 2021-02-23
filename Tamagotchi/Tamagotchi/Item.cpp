#include "Item.h"
#include "Pet.h"
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
	string type, string name, int itemId, int prince, string description, int hpChange, bool evoStone,int foodChange, int happinessChange, bool minigameLife, float xpCoupon, int poopChange)
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
	this->poopChange = poopChange;
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
		description = "The fluffy cheesecake that perfectly sweet with a light and delicate texture, all wrapped in a crunchy Graham cracker and toasted pecan crust";
		hpChange =-10;
		evoStone = false;
		foodChange = 20;
		happinessChange = 25;
		minigameLife = false;
		xpCoupon = 0.0;
		this->poopChange = 5;
	}
	else if (name=="honeyPeachSoda")
	{
		type = "food";
		itemId = 2;
		price = 15;
		this->description = "A nice addition to a meal especially when outdoors.";
		this->hpChange = 5;
		this->evoStone = false;
		this->foodChange = 15;
		this->happinessChange = -5;
		this->minigameLife = false;
		this->xpCoupon = 0.0;
		this->poopChange = 5;
	}
	else if (name=="milk")
	{
		type = "food";
		itemId = 3;
		this->price = 20;
		this->description = "Everyone know that milk is milk , nothing to describe about this thing.";
		this->hpChange = 10;
		this->evoStone = false;
		this->foodChange = 15;
		this->happinessChange = 5;
		this->minigameLife = false;
		this->xpCoupon = 0.0;
		this->poopChange = 2;
	}
	else if (name=="noodle69")
	{
		type = "food";
		itemId = 4;
		this->price = 69;
		this->description = "The super ultra mega ultimate noodle that the world ever have.";
		this->hpChange = 69;
		this->evoStone = false;
		this->foodChange = 69;
		this->happinessChange = 0;
		this->minigameLife = false;
		this->xpCoupon = 0.0;
		this->poopChange = 69;
	}
	else if (name=="icecream")
	{
		type = "food";
		itemId = 5;
		this->price = 5;
		this->description = "A sweetened frozen food that every fat boy in the world love, contain a ton of callories";
		this->hpChange = -5;
		this->evoStone = evoStone;
		this->foodChange = 15;
		this->happinessChange = 0;
		this->minigameLife = minigameLife;
		this->xpCoupon = xpCoupon;
		this->poopChange = 5;
	}
	else if (name=="yamRoll")
	{
		type = "food";
		itemId = 6;
		this->price = 25;
		this->description = "Light, soft and cottony cake";
		this->hpChange = 5;
		this->evoStone = false;
		this->foodChange = 30;
		this->happinessChange = 10;
		this->minigameLife = false;
		this->xpCoupon = 0.0;
		this->poopChange = 10;

	}
	else {
		type = "not Item";
		itemId = 10;
		this->price = 0;
		this->description = "Item not set";
		this->hpChange = 0;
		this->evoStone = false;
		this->foodChange = 0;
		this->happinessChange = 0;
		this->minigameLife = false;
		this->xpCoupon = 0.0;
		this->poopChange = 0;
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
	this->poopChange = poopChange;
}
Item::~Item() {

}

void Item::UseItem(Pet *pet) {
	pet->currentHp += hpChange;
	pet->currentExp += xpCoupon;
	pet->currentHappiness += happinessChange;
	pet->currentFood += foodChange;
	pet->currentPoop += poopChange;
	//pet->hpChangeRateMultiplier +=  in to the Fu....
	//pet->expChangeMultiplier +=
	//pet->foodChangeMultiplier +=
	//pet->happinessChangeMultiplier +=
	//pet->poopChangeMultiplier +=
	pet->ateEvolveStone = evoStone;

	pet->Clamp(&pet->currentHp, pet->hpMax[pet->currentLevel]);
	pet->Clamp(&pet->currentExp, pet->expPerEvolve[pet->currentLevel]);
	pet->Clamp(&pet->currentHappiness, pet->happinessMax[pet->currentLevel]);
	pet->Clamp(&pet->currentFood, pet->foodMax[pet->currentLevel]);
	pet->Clamp(&pet->currentPoop, pet->poopMax[pet->currentLevel]);
	
}