#include "BlockBP.h"

BlockBP::BlockBP(string filepath, string type , string name)
{
	Border.SetDimensions(Vector2f(250.0f , 320.0f));
	Border.SetTexture("Assets/Textures/border.png");
	Border.rectangleShape.setFillColor(Color::Yellow);

	font.loadFromFile("Assets/Fonts/Minecraftia.ttf");
	DES.setFont(font);
	DES.setString(name);
	DES.setFillColor(Color::Red);

	Object.SetTexture(filepath);

	this->type = type;

	if (type == "BG") {
		Object.SetDimensions(Vector2f(210.0f , 300.0f));
	}
	else if (type == "PF") {
		Object.SetDimensions(Vector2f(170.0f, 170.0f));
	}

}

BlockBP::~BlockBP()
{
}

void BlockBP::SetPos(Vector2f pos)
{
	Border.SetPosition(pos);
	if (type == "BG") {
		Object.SetPosition(Vector2f(pos.x + 20.0f, pos.y + 10.0f));
	}
	else if (type == "PF") {
		Object.SetPosition(Vector2f(pos.x + 40.0f, pos.y + 70.0f));
	}
	DES.setPosition(Vector2f(pos.x, pos.y + 230.0f));
}

void BlockBP::Draw(RenderWindow& window)
{
	Border.Draw(window);
	Object.Draw(window);
	window.draw(DES);
}
