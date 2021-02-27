#pragma once

#include "GravityObject.h"
#include "PlatformObject.h"
#include "PowerUp.h"
#include <SFML/Audio.hpp>

class Doodle
{
public :
	Doodle();
	~Doodle();

	void Initialize();										// Call to initialize doodle 
	void Update(float deltaTime);							// Update to GravityObject and PlatformObject
	void Draw(RenderWindow& window , float time_interval);	// Draw GravityObject and PlatformObject

	int gamestate = 0;										// 0 - Start, 1 - Playing, 2 - Gameover

	GravityObject* Alpha;
	PlatformObject* Platform;
	PowerUp* Power;
	
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

	Sound sound, music , pw;
	SoundBuffer soundB , musicB , pwB;

	int windowWidth = 720;
	int windowHeight = 1040;

	int difficulty = 0;				// Adjust difficulty and score speed rate 
	int score = 0;
	int difficulty_rate = 20;
	int score_rate = 1000;
	float finalspeed_rate = 0.1f;

	int FadeCnt = 0;				// Fade VFX
	float FadeRate = 0.05f;
	
	bool sw = false;				// Blink VFX

};

