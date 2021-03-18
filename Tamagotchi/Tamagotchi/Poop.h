#pragma once
#include <SFML/Audio.hpp>
#include <iostream>
#include <unordered_map>
#include <vector>
#include "GameObject.h"

using std::unordered_map;
using std::vector;

class Poop :
    public GameObject
{
public:
	Poop();
	Poop(Vector2f position, Vector2f dimensions, bool originIsCenter,
		string texturePath, Vector2u imageCount, Vector2i start, Vector2i finish, float frameTime, int nClickToDestroy = 3, float floorLine = 1040/2); //Proper Animation
	~Poop();

	void Initialize();

	bool Update(float deltaTime, RenderWindow& window, unordered_map<string, bool>& mousePress, Vector2i& mousePosition);


	void OnClick();
	void OnHover();

	bool IsMouseOver(Vector2i& mousePosition);


	int nClickToDestroy;
	int price = 1;
	int startingPrice = 10;
	int priceRange = 10;

	float basePoopSize = 1;
	float lowestPoopSize = 0.3f;
	float floorLine = 1040/2;
	float gravity = 9.8f * 300 / 2;
	
	vector<Sound> sfx;
	vector<SoundBuffer> soundBuffers;
	struct SoundVariables {
		string filePath = "";
		float volume = 15.0f;
	};
	float sfxVolume = 15;
	vector<SoundVariables> sfxVariables = {
		{"Assets/Sounds/Pet/pet_poop_splash.wav", sfxVolume},
	};
};

