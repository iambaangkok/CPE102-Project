#pragma once
#include <SFML/Graphics.hpp>
#include"Button.h"
#include"Pet.h"
#include"Item.h"
#include <vector>
#include <iostream>
using namespace sf;

using std::cout;
using std::endl;

class Button;

class Shop
{
public:
	Shop();
	/*Shop(vector<Item> items, Text description, Text price, Text totalPrice,	Text amount, GameObject bg,	GameObject scrollbar,
		Button food, Button dessert, Button booster); */
	~Shop();
	void Initialize();
	void Update(float deltaTime,int mouseWheelDelta );
	void Draw(RenderWindow &window);
	void AddItem(string,string);

	int speedscroll = 600;
	bool isOpen = true;
	int windowWidth = 720;
	int windowHeight = 1040;
	int topscroll = 200;
	int lowscroll = 760;
	int positionscrollX = 710;
	int heightscrollbar = 150;
	int corePosition = 310;
	float corePositiony = 270;
	int heightfood = 4 * 180;
	int heightcandy = 4 * 180;
	int heightetc = 4 * 180;
	

	Vector2f position = Vector2f(0,0);
	//Item* test1;
	vector<Item*> itemfood;
	vector<Item*> itemcandy;
	vector<Item*> itemetc;
	vector<Item*> items;
	vector<Text> descriptions;
	vector<Text> prices;
	GameObject* bg;
	GameObject* bgbar;
	GameObject* scrollbar;
	GameObject* picitem;
	GameObject* up;
	GameObject* low;
	vector<Button*> buttons;//0 = food, 1 = dessert, 2 = booster;

};

