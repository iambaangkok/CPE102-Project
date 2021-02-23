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




	float speedscroll = 300;
	bool isOpen = false;
	int windowWidth = 720;
	int windowHeight = 1040;
	int topscroll = 0;
	int lowscroll = 200;
	Vector2f position = Vector2f(0,0);
	vector<Item> items;
	vector<Text> descriptions;
	vector<Text> prices;
	GameObject *bg;
	GameObject *scrollbar;
	vector<Button> buttons;//0 = food, 1 = dessert, 2 = booster;
};

