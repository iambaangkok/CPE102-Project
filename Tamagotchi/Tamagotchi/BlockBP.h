#pragma once

#include "GameObject.h"

class BlockBP
{
public :
	BlockBP(string filepath , string type , string name);
	~BlockBP();

	void SetPos(Vector2f pos);
	void Draw(RenderWindow &window);

	GameObject Border , Object ;
	Text DES;
	string type;
	Font font;
};

