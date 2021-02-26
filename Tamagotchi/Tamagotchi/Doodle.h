#pragma once

#include "GravityObject.h"
#include "PlatformObject.h"
#include <SFML/Audio.hpp>

class Doodle
{
public :
	Doodle();
	~Doodle();

	void Initialize();
	void Update(float deltaTime);
	void Draw(RenderWindow& window , float time_interval);

	GravityObject* Alpha;
	PlatformObject* Platform;

	vector<Sprite> background;

	Font font;
	Text scoreText;
	Texture backgroundtexture;
	Sprite Logo1, Logo2;
	Texture Logo1T , Logo2T;
	Sprite Press;
	Texture PressT;
	Sprite YOUDIED; 
	Texture YOUDIEDT;

	SoundBuffer buffer , buffer2;
	Sound sound;
	Sound music;

	int windowWidth = 720;
	int windowHeight = 1040;

	int difficulty = 0;
	int score = 0;
	int difficulty_rate = 50;
	int score_rate = 500;

	int gamestate = 0; // 0 - Start, 1 - Playing, 2 - Gameover
	int cnt = 0;
	float FadeRate = 0.05f;

	bool sw = false;
};

