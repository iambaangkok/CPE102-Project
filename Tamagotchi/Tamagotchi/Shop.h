#pragma once
#include <SFML/Graphics.hpp>
#include"Button.h"
#include"Pet.h"
#include"Item.h"
#include"Doodle.h"
#include <vector>
#include <iostream>
using namespace sf;

using std::cout;
using std::endl;

class Button;

class Shop
{
public:
	Shop(int& gstate, Pet& pet, Doodle& doodle);
	/*Shop(vector<Item> items, Text description, Text price, Text totalPrice,	Text amount, GameObject bg,	GameObject scrollbar,
		Button food, Button dessert, Button booster); */
	~Shop();
	void SetTextShop(Text& text, string str, Font& font, Color color, int size, Vector2f position = Vector2f(720 / 2, 1040 / 2));

	void Initialize();
	void Update(float deltaTime,int mouseWheelDelta,
		RenderWindow& window, unordered_map<string, bool>& mousePress, unordered_map<string, bool>& mouseHold, Vector2i& mousePosition,
		bool& quitGame, int& selectedPet, bool& clearSave, bool& muteBgm, bool& muteSfx, Button& foodButton, Button& candyButton, Button& etcc);
	void Draw(RenderWindow &window);
	void AddItem(string,string, int& , Shop* , Pet& , Doodle& );
	
	int speedscroll = 700;
	bool isOpen = false;
	int windowWidth = 720;
	int windowHeight = 1040;
	int topscroll = 200;
	int lowscroll = 760;
	int positionscrollX = 710;
	int heightscrollbar = 150;
	int corePosition = 310;
	float corePositiony = 270;

	int heightfood = itemfood.size() * 180;
	int heightcandy = itemcandy.size() * 180;
	int heightetc = itemetc.size() * 180;
	
	string status = "food";
	Font font;
	Color col_BLACK1 = Color(24, 20, 37);

	Vector2f position = Vector2f(0,0);
	
	vector<Item*> itemfood;
	vector<Item*> itemcandy;
	vector<Item*> itemetc;
	vector<Item*> items;
	vector<Button*> buy1;
	vector<Button*> buy2;
	vector<Button*>buy3;
	vector<Text> descriptions;
	vector<Text> prices;
	GameObject* bg;
	GameObject* bgbar;
	GameObject* scrollbar;
	GameObject* picitem;
	GameObject* up;
	GameObject* low;
	GameObject* buy;
	vector<Text> text;
	//vector<vector<Text>> text;
	vector<vector<Text>> food;
	vector<vector<Text>> candy;
	vector<vector<Text>> etc;
	vector<Vector2f> textofset; 
	vector<Button*> buttons;//0 = food, 1 = dessert, 2 = booster;

};

