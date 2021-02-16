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
	Shop(vector<Item> items, Text description, Text price, Text totalPrice,	Text amount, GameObject bg,	GameObject scrollbar,
		Button food, Button dessert, Button booster); 
	~Shop();
	

	vector<Item> items;
	Text description;
	vector<Text> price;
	GameObject bg;
	GameObject scrollbar;
	vector<Button> buttons;



};

