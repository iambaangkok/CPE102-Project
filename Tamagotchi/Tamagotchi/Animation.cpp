#include <SFML/Graphics.hpp>
#include "Animation.h"

using namespace sf;



Animation::Animation() {
    frameTime = 0.0f;
    totalTime = 0.0f;
}

Animation::Animation(Texture* texture, Vector2u imageCount, float frameTime) {
    this->imageCount = imageCount;
    this->frameTime = frameTime;
    totalTime = 0.0f;
    currentImage.x = 0;

    uvRect.width = texture->getSize().x / float(imageCount.x);
    uvRect.height = texture->getSize().y / float(imageCount.y);
}

Animation::~Animation() {

}

void Animation::Update(int row, float deltaTime, bool faceRight) {
    if (!enabled) {
        return;
    }

    currentImage.y = row;

    if (!freezeFrame) {
        totalTime += deltaTime;

        if (totalTime >= frameTime) {
            totalTime -= frameTime;
            currentImage.x++;
            if (currentImage.x >= imageCount.x) {
                currentImage.x = 0;
            }
        }
    }

    uvRect.top = currentImage.y * uvRect.height;
    if (faceRight) {
        uvRect.left = currentImage.x * uvRect.width;
        uvRect.width = abs(uvRect.width);
    }
    else {
        uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
        uvRect.width = -abs(uvRect.width);
    }
}

void Animation::SetFrameTime(float frameTime) {
    this->frameTime = frameTime;
}

void Animation::SetTexture(Texture* texture) {
    
}

void Animation::SetFrame(Vector2u rowColumn) {
    currentImage.y = rowColumn.x;
    currentImage.x = rowColumn.y;
}
