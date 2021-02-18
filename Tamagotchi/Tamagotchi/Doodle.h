#pragma once

#include "GravityObject.h"
#include "PlatformObject.h"
#include <SFML/Audio.hpp>

class Doodle
{
public :
	Doodle();
	~Doodle();

	void Initialize(PlatformObject &Platform);
	void Update(GravityObject &Alpha , PlatformObject &Platform , RenderWindow& window);
	void Draw(GravityObject& Alpha, PlatformObject& Platform , RenderWindow& window);

	Font font;
	Text scoreText;
	Sprite background;
	Texture backgroundtexture;

	SoundBuffer buffer , buffer2;
	Sound sound;
	Sound music;
	
	int windowWidth = 720;
	int windowHeight = 1040;

	int difficulty = 0;

	int score = 0;

	bool gameover = false;

};

