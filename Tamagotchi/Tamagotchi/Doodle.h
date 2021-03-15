#pragma once

#include "GravityObject.h"
#include "PlatformObject.h"
#include "PowerUp.h"
#include "BlockBP.h"
#include <unordered_map>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <random>
#include "Pet.h"

class Doodle
{
public :
	Doodle(int& maingame_state , Pet& pet);
	~Doodle();

	void Initialize(int curlevel);														// Call to initialize doodle 
	void Update(float deltaTime , unordered_map<string, bool> &key , int curlevel , Pet &pet);		// Update to GravityObject and PlatformObject
	void Draw(RenderWindow& window);													// Draw GravityObject and PlatformObject
	void SetBG(string filepath);
	void SetSpriteCenter(Sprite &S);
	void SetTextCenter(Text& T);

	int gstate = -1;										// 0 - Start, 1 - Playing, 2 - Gameover , 3 - Background Customization
	int* maingame_state;
	bool callgame = false;

	GravityObject* Alpha;
	PlatformObject* Platform;
	GameObject* land;
	float land_posy;
	PowerUp* Power , * CoinP;
	
	Font font;
	Text scoreText , highscoreText , money;
	vector<Sprite> background; 
	vector<float> background_posy;
	Sprite Logo1, Logo2 , Press , YOUDIED , SelectBG;
	Texture backgroundT , Logo1T, Logo2T , PressT , YOUDIEDT , SelectBGT;

	Sound sound, music , pw , dead , coin;
	SoundBuffer soundB , musicB , pwB ,deadB , coinB;

	int curlevel = 0;

	int windowWidth = 720;
	int windowHeight = 1040;

	int difficulty = 0;				// Adjust difficulty and score speed rate 
	int score = 0;
	int difficulty_rate = 25;
	int score_rate = 30;
	float finalspeed_rate = 0.1f;
	int Money = 0;
	int MoneyPickup = 0;
	int money_rate = 5;
	int highscore = 0;

	int FadeCnt = 0;				// Fade VFX
	float FadeRate = 2.0f;

	int power_range = 30;
	int coin_range = 19;

	int equip = 1;					// Background Customization
	int select = 1;
	int no_pic = 4;
	BlockBP* BP ,* BPL ,* BPR;
};

