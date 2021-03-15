#pragma once
#include <iostream>
#include <chrono>
#include <ctime>  
#include <vector>
#include <unordered_map>
#include <SFML/Audio.hpp>
#include "GameObject.h"
#include "Item.h"
#include "Poop.h"

using std::vector;
using std::unordered_map;
class Item;

class Pet :
    public GameObject
{
public:
	Pet();
	Pet(Vector2f position, Vector2f dimensions, bool originIsCenter,//Proper Animation
		string texturePath, Vector2u imageCount, Vector2i start, Vector2i finish, float frameTime);
	Pet(Vector2f position, Vector2f dimensions, bool originIsCenter,//Customize Pet
		string texturePath, Vector2u imageCount, Vector2i start, Vector2i finish, float frameTime,
		string name, string type, int levelMax, vector<float> hpMax, vector<float> expPerEvolve, vector<float> happinessMax, vector<float> foodMax, vector<float> poopMax,
		int hpChangeRate = 1, int expChangeRate = 1, int foodChangeRate = 20, int happinessChangeRate = 1, int poopChangeRate = 1, float notEnoughFoodThreshold = 0.2f);
	Pet(Vector2f position, Vector2f dimensions, bool originIsCenter,//By Type
		string texturePath, Vector2u imageCount, Vector2i start, Vector2i finish, float frameTime, 
		string name, string type);
	~Pet();


	void Initialize();//Runs before everything else in every game loop/ reset variable that needs to be reset every game loop

	void Update(float deltaTime, unordered_map<string, bool>& keyPress, unordered_map<string, bool>& keyHold, unordered_map<string, bool>& keyRelease,
		unordered_map<string, bool>& mousePress, unordered_map<string, bool>& mouseRelease, unordered_map<string, bool>& mouseHold, Vector2i mousePosition, int mouseWheelDelta);

	void Draw(RenderWindow& window);


	void PlaySound(Sound& soundPlayer, int soundBufferIndex, string type = "SFX");

	bool CanPoop();
	Poop* CreatePoop();

	template <typename T>
	void Clamp(T* clampVariable, T upperClamp = 0, T lowerClamp = 0); //Ensure that clampVariable will be in between [lowerClamp,upperClamp]

	void UseItem(int itemID); //Use Item

	bool IsMouseOver(Vector2i& mousePosition);



	///Time Related Variables: all time in seconds
	long long int time_sinceBirth = 0;
	long long int time_lastSession = 0;
	long long int time_sinceLastSession = 0;
	long long int time_currentSession = 0;
	long long int time_currentTime_sinceEpoch = 0;
	long long int time_alive = 0;

	///Stats
	float totalTime = 0;
	int tickTime = 1;

	bool isAlive = true;
	int money = 0;
	string name = "Unset Name";
	string type = "Unset Type";
	int currentLevel = 0;
	float currentHp = 0;
	float currentExp = 0;
	float currentHappiness = 0;
	float currentFood = 0;
	float currentPoop = 0;

	bool ateEvolveStone = false;

	float hpChangeRateMultiplier = 1.0f;
	float expChangeMultiplier = 1.0f;
	float foodChangeMultiplier = 1.0f;
	float happinessPoint = 1.0f;
	float happinessChangeMultiplier = 1.0f;
	float poopChangeMultiplier = 1.0f;

	int levelMax = 0;
	vector<float> hpMax; //HP
	vector<float> expPerEvolve; //EXP
	vector<float> happinessMax; //Happiness
	vector<float> foodMax; //Food
	vector<float> poopMax; //Poop

	//All Rate are at X per Y tickTime(default to 1 seconds);
	float hpChangeRate = 1;
	float expChangeRate = 1;
	float foodChangeRate = 1;
	float happinessChangeRate = 1;
	float baseHappinessChangeRate = 1;
	float poopChangeRate = 1;

	float notEnoughFoodThreshold = 0.2f; //If Food is BELOW currentFood * this multiplier, HP , Happiness , starts to decay


	///Moving
	Vector2f speed = Vector2f(0,0);
	Vector2f maxSpeed = Vector2f(125,125);
	float runSpeedMultiplier = 1.75f;
	bool isMoving = false;

	///Random Movement
	float randomMovementInterval = 5;
	float randomMovementIntervalTime = 0;
	float randomMovementMoveTime = 1;
	float randomMovementMoveTotalTime = 0;
	bool isRandomlyMoving = false;
	Vector2f randomMoveSpeed = Vector2f(0, 0);

	///Shadow
	GameObject* shadow;
	float shadowNormalYOffset = 50;
	float shadowYOffset = shadowNormalYOffset;
	vector<GameObject> shadowBorder; //0 = right, 1 = left, 2 = bottom, 3 = top

	///Jumping
	float gravity = 9.8f * 300/2;
	float jumpAcceleration = 100 * 10/1.5; //- x speedY;
	float shadowYOffsetSpeed = 0;
	bool isInAir = false;
	bool isInAirLastFrame = false;

	///Dragging
	bool mouseIsOver = false;
	bool isDraggedByMouse = false;
	Vector2f mousePositionRelativeToPet = Vector2f(0, 0);
	Vector2f lastFramePosition = Vector2f(0, 0);
	Vector2f deltaPosition = Vector2f(0, 0);
	Vector2f throwSpeed = Vector2f(0, 0);
	float windResistance = 120/2; // same as gravity but in x

	///Sound
	vector<Sound> sfx;
	vector<SoundBuffer> soundBuffers;
	struct SoundVariables {
		string filePath = "";
		float volume = 15.0f;
	};
	float sfxVolume = 15;
	vector<SoundVariables> sfxVariables = {
		{"Assets/Sounds/Pet/pet_walk_01.wav", sfxVolume },
		{"Assets/Sounds/Pet/pet_walk_02.wav", sfxVolume },
		{"Assets/Sounds/Pet/pet_walk_03.wav", sfxVolume },
		{"Assets/Sounds/Pet/pet_jump.wav", sfxVolume },
		{"Assets/Sounds/Pet/pet_land_onground.wav", sfxVolume },
		{"Assets/Sounds/Pet/pet_fart01.wav", sfxVolume},
		{"Assets/Sounds/Pet/pet_fart02.wav", sfxVolume},
		{"Assets/Sounds/Pet/pet_fart03.wav", sfxVolume}
	};
	
	
	
	

};

