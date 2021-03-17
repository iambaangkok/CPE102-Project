#pragma once

#include "GameObject.h"
#include <string>

class BlockBP
{
public :
	BlockBP(string filepath);
	~BlockBP();

	void SetPos(Vector2f pos);
	void Draw(RenderWindow &window);

	GameObject Border , Object ;
	Font font;
	Text text;
};

