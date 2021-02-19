#pragma once
#include "GameObject.h"
#include "Pet.h"
class Pet;

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
		string type,string name,int itemId,int prince, string description, int hpChange, bool evoStone,
		int foodChange, int happinessChange, bool minigameLife, float xpCoupon,int poopChange);//Item in shop.
	Item(Vector2f position, Vector2f dimensions, bool originIsCenter, string texturePath, Vector2u imageCount, Vector2i start, Vector2i finish, float frameTime,
		string name);
	
	~Item();
	
	void UseItem(Pet *pet);

	string type;
	string name;
	int itemId;
	int price;
	string description;
	int hpChange;
	bool evoStone;
	int foodChange;
	int happinessChange;
	bool minigameLife;
	float xpCoupon;
	int poopChange;
	
};

