#include "BlockBP.h"

BlockBP::BlockBP(string filepath)
{
	float size_x = 720.0f / 1.60f;
	float size_y = 1040.0f / 1.60f;
	float offset = 20.0f;

	Object.SetTexture(filepath);
	Object.SetDimensions(Vector2f(size_x , size_y));
	Object.SetOrigin(Vector2f(size_x / 2.0f, size_y / 2.0f));

	Border.SetDimensions(Vector2f(size_x + offset , size_y + offset));
	Border.SetTexture("Assets/Textures/Orange.png");
	Border.SetOrigin(Vector2f((size_x + offset) / 2.0f, (size_y + offset) / 2.0f));
}

BlockBP::~BlockBP()
{
}

void BlockBP::SetPos(Vector2f pos)
{
	Border.SetPosition(pos);
	Object.SetPosition(pos);
}

void BlockBP::Draw(RenderWindow& window)
{
	Border.Draw(window);
	Object.Draw(window);
}
