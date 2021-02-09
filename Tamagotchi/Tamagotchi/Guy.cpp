#include "Guy.h"

Guy::Guy() : GameObject() {

}

Guy::Guy(Vector2f position, Vector2f dimensions, bool originIsCenter, string texturePath, Vector2u imageCount, float frameTime)
	 : GameObject(position, dimensions, originIsCenter, texturePath, imageCount, frameTime) { //Animation from Texture Sheet

	rectangleShape = RectangleShape(dimensions);
	rectangleShape.setPosition(position);
	if (originIsCenter) {
		rectangleShape.setOrigin(Vector2f(dimensions.x / 2, dimensions.y / 2));
	}

	if (texture.loadFromFile(texturePath)) {
		cout << "Loaded " + texturePath << endl;
	}
	rectangleShape.setTexture(&texture);

	animation = Animation(&texture, imageCount, frameTime);
}