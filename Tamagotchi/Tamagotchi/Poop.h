#pragma once
#include <iostream>
#include <unordered_map>
#include "GameObject.h"

using std::unordered_map;


class Poop :
    public GameObject
{
public:
	Poop();
	Poop(Vector2f position, Vector2f dimensions, bool originIsCenter,
		string texturePath, Vector2u imageCount, Vector2i start, Vector2i finish, float frameTime, int nClickToDestroy = 3); //Proper Animation
	~Poop();

	void Initialize();

	void Update(float deltaTime, RenderWindow& window, unordered_map<string, bool>& mousePress, Vector2i& mousePosition);


	void OnClick();
	void OnHover();

	bool IsMouseOver(Vector2i& mousePosition);


	int nClickToDestroy;
	float basePoopSize = 1;
	float lowestPoopSize = 0.6f;

};

