#include "BlockBP.h"

BlockBP::BlockBP(string filepath, string name)
{
	Border.SetDimensions(Vector2f(720.0f / 1.50f , 1040.0f / 1.50f));
	Border.SetTexture("Assets/Textures/border.png");
	Border.rectangleShape.setFillColor(Color::Yellow);
	Border.SetOrigin(Vector2f(720.0f / 3.0f, 1040.0f / 3.0f));

	font.loadFromFile("Assets/Fonts/Minecraftia.ttf");
	DES.setFont(font);
	DES.setString(name);
	DES.setFillColor(Color::Red);

	Object.SetTexture(filepath);
	Object.SetDimensions(Vector2f(720.0f / 1.60f, 1040.0f / 1.60f));
	Object.SetOrigin(Vector2f(720.0f / 3.20f, 1040.0f / 3.20f));
}

BlockBP::~BlockBP()
{
}

void BlockBP::SetPos(Vector2f pos)
{
	Border.SetPosition(pos);
	Object.SetPosition(pos);
	DES.setPosition(pos);
}

void BlockBP::Draw(RenderWindow& window)
{
	Border.Draw(window);
	Object.Draw(window);
	window.draw(DES);
}
