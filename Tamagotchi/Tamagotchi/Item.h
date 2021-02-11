#pragma once
#include "GameObject.h"
class Item :
    public GameObject
{
public:
	Item();
	Item(Vector2f position, Vector2f dimensions, bool originIsCenter,
		string texturePath = "Assets/Textures/testTextureLARGE.png"); //Single Texture
	Item(Vector2f position, Vector2f dimensions, bool originIsCenter,
		string texturePath, Vector2u imageCount, float frameTime); //1Row Animation from Texture Sheet
	Item(Vector2f position, Vector2f dimensions, bool originIsCenter,
		string texturePath, Vector2u imageCount, Vector2i imageCoordinate); //Single Texture from Texture Sheet
	Item(Vector2f position, Vector2f dimensions, bool originIsCenter,
		string texturePath, Vector2u imageCount, Vector2i start, Vector2i finish, float frameTime); //Proper Animation
	Item(Vector2f position, Vector2f dimensions, bool originIsCenter, string texturePath, Vector2u imageCount, Vector2i start, Vector2i finish, float frameTime, 
		string name, string description, int hpChange, bool evoStone,
		int foodChange, int happinessChange, bool minigameLife, float xpCoupon);//Item in shop.
	~Item();
	string name;
	string description;
	int hpChange;
	bool evoStone;
	int foodChange;
	int happinessChange;
	bool minigameLife;
	float xpCoupon;
};

