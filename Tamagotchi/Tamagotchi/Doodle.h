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
#include "ParticleSystem.h"

class Doodle
{
public :
	Doodle(int& maingame_state , Pet& pet);
	~Doodle();

	void Reset(Pet &pet);														// Call to initialize doodle 
	void Update(float deltaTime , unordered_map<string, bool> &key , int curlevel , Pet &pet);		// Update to GravityObject and PlatformObject
	void Draw(RenderWindow& window);													// Draw GravityObject and PlatformObject
	
	void InitSound(float musicVolume, float soundVolume);
	void InitBGMenu();
	void InitSprite();
	void InitText();
	void InitBG();

	void SetSpriteCenter(Sprite &S);
	void SetTextCenter(Text& T);

	void muteBGM(bool mute);
	void muteSFX(bool mute);

	int gstate = -1;										// 0 - Start, 1 - Playing, 2 - Gameover , 3 - Background Customization
	int* maingame_state;

	GravityObject* Alpha;
	PlatformObject* Platform;
	GameObject* land;
	PowerUp* Power , * CoinP;
	ParticleSystem* landing;

	Font font;
	Text scoreText , highscoreText , money;
	vector<Sprite> background; 
	Sprite Logo1, Logo2 , Press , YOUDIED , SelectBG , Lock;
	Texture backgroundT , Logo1T, Logo2T , PressT , YOUDIEDT , SelectBGT , LockT;

	vector<float> background_posy;
	float land_posy;

	Sound sound, music , pw , dead , coin;
	SoundBuffer soundB , musicB , pwB ,deadB , coinB;

	int curlevel = 0;

	float windowWidth = 720.0f;
	float windowHeight = 1040.0f;

	int difficulty = 0;				// Adjust difficulty and score speed rate 
	int score = 0;
	int difficulty_rate = 25;
	int score_rate = 30;
	float finalspeed_rate = 0.1f;
	int Money = 0;
	int MoneyPickup = 0;
	int money_rate = 5;
	int highscore = 0;

	int power_range = 30;			//Powerup and Coin customization
	int coin_range = 19;

	int FadeCnt = 0;				// Fade VFX
	float FadeRate = 2.0f;

	int equip = 1;					// Background customization
	int no_pic = 4;
	vector<BlockBP*> BGMenu;

	int landing_ind = 0;

	Text unlocked;
	int unlocklvl[5] = { 0,0,10,20,30 };
};

