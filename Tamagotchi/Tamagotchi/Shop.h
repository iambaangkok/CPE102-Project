#pragma once
#include"GameObject.h"
#include"Pet.h"
#include"Item.h"
#include"Button.h"
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
	Button food;
	Button dessert;
	Button booster;



};

