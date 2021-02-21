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
	void Update(RenderWindow& window);
	void Draw(RenderWindow& window);

	GravityObject* Alpha;
	PlatformObject* Platform;

	Font font;
	Text scoreText;
	Sprite background;
	Texture backgroundtexture;
	Sprite Logo1, Logo2;
	Texture Logo1T , Logo2T;
	Sprite Press;
	Texture PressT;

	SoundBuffer buffer , buffer2;
	Sound sound;
	Sound music;
	
	float acc = 1.0f;

	int windowWidth = 720;
	int windowHeight = 1040;

	int difficulty = 0;
	int score = 0;

	int gamestate = 0; // 0 - Start, 1 - Playing, 2 - Gameover

};

