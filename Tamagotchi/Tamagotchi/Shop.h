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
	void SetTextShop(Text& text, string str, Font& font, Color color, int size, Vector2f position = Vector2f(720 / 2, 1040 / 2));

	void Initialize();
	void Update(float deltaTime,int mouseWheelDelta );
	void Draw(RenderWindow &window);
	void AddItem(string,string);
	
	int speedscroll = 600;
	bool isOpen = false;
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
	string status = "food";
	int status1 = 1;
	Font font;
	Color col_BLACK1 = Color(24, 20, 37);

	Vector2f position = Vector2f(0,0);
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
	vector<Text> text;
	//vector<vector<Text>> text;
	vector<vector<Text>> food;
	vector<vector<Text>> candy;
	vector<vector<Text>> etc;
	vector<Button*> buttons;//0 = food, 1 = dessert, 2 = booster;

};

