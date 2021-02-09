#pragma once
#include "GameObject.h"
class Guy : public GameObject{
public:
	Guy();
	Guy(Vector2f position, Vector2f dimensions, bool originIsCenter,
		string texturePath); //Single Texture
	Guy(Vector2f position, Vector2f dimensions, bool originIsCenter,
		string texturePath, Vector2u imageCount, float frameTime); //Animation from Texture Sheet
	~Guy();
	
	//Fuck

private:


protected:

};

