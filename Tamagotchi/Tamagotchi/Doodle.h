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
	void Update(float deltaTime , unordered_map<string, bool> &key , int curlevel);		// Update to GravityObject and PlatformObject
	void Draw(RenderWindow& window);													// Draw GravityObject and PlatformObject
	void SetBackground(string filepath);

	int gstate = -1;										// 0 - Start, 1 - Playing, 2 - Gameover , 3 - Background Customization
	int* maingame_state;
	bool callgame = false;

	GravityObject* Alpha;
	PlatformObject* Platform;
	GameObject* land;
	float land_posy;
	PowerUp* Power;
	

	Font font;
	Text scoreText , highscoreText;
	vector<Sprite> background; 
	vector<float> background_posy;
	Sprite Logo1, Logo2;
	Sprite Press;
	Sprite YOUDIED;

	Texture backgroundT;
	Texture Logo1T, Logo2T;
	Texture PressT;
	Texture YOUDIEDT;

	Sound sound, music , pw , dead;
	SoundBuffer soundB , musicB , pwB ,deadB;

	int curlevel = 0;

	int windowWidth = 720;
	int windowHeight = 1040;

	int difficulty = 0;				// Adjust difficulty and score speed rate 
	int score = 0;
	int difficulty_rate = 25;
	int score_rate = 30;
	float finalspeed_rate = 0.3f;

	int highscore = 0;

	int FadeCnt = 0;				// Fade VFX
	float FadeRate = 2.0f;

	int beta; 
	int power_range = 50;

	int equip = 1;					// Background Customization
	int select = 1;
	BlockBP* BP;
};

