#pragma once

#include "GravityObject.h"
#include "PlatformObject.h"
#include "PowerUp.h"
#include "BlockBP.h"
#include <unordered_map>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <random>

class Doodle
{
public :
	Doodle(int& maingame_state);
	~Doodle();

	void Initialize();										// Call to initialize doodle 
	void Update(float deltaTime , unordered_map<string, bool> &key);							// Update to GravityObject and PlatformObject
	void Draw(RenderWindow& window);	// Draw GravityObject and PlatformObject

	int gstate = -1;										// 0 - Start, 1 - Playing, 2 - Gameover
	int* maingame_state;
	bool callgame = false;

	GravityObject* Alpha;
	PlatformObject* Platform;
	GameObject* land;
	float land_posy;
	PowerUp* Power;
	BlockBP* BP;

	Font font;
	Text scoreText;
	vector<Sprite> background;
	Sprite Logo1, Logo2;
	Sprite Press;
	Sprite YOUDIED;

	Texture backgroundT;
	Texture Logo1T, Logo2T;
	Texture PressT;
	Texture YOUDIEDT;

	Sound sound, music , pw , dead;
	SoundBuffer soundB , musicB , pwB ,deadB;

	int windowWidth = 720;
	int windowHeight = 1040;

	int difficulty = 0;				// Adjust difficulty and score speed rate 
	int score = 0;
	int difficulty_rate = 40;
	int score_rate = 20;
	float finalspeed_rate = 0.3f;

	int FadeCnt = 0;				// Fade VFX
	float FadeRate = 2.0f;
	
	bool sw = false;				// Blink VFX

	int beta; 
	int power_range = 50;
};

