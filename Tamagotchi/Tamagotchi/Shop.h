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
	void Update(float detatime );
	void Draw(RenderWindow &window);

	bool isOpen = false;
	int windowWidth = 720;
	int windowHeight = 1040;
	int topscroll = 0; // ระดับของแท่งเลื่อน
	int lowscroll = 100;
	Vector2f position = Vector2f(0,0);

	vector<Item> items;
	vector<Text> descriptions;
	vector<Text> prices;
	GameObject *bg;
	GameObject *scrollbar;
	vector<Button> buttons;//0 = food, 1 = dessert, 2 = booster;
};

