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

    //this->Update()
}

Animation::~Animation() {

}

//1Row Animation
void Animation::Update(int row, float deltaTime, bool faceRight) {
    if (!enabled) {
        return;
    }

    if (!freezeFrame) {
        currentImage.y = row;

        totalTime += deltaTime;

        if (totalTime >= frameTime) {
            totalTime -= frameTime;
            currentImage.x++;
            if (currentImage.x >= imageCount.x) {
                currentImage.x = 0;
            }
        }
        uvRect.top = currentImage.y * uvRect.height;
    }
    
    /*if (faceRight) {
        uvRect.left = currentImage.x * uvRect.width;
        uvRect.width = abs(uvRect.width);
    }
        uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
        uvRect.width = -abs(uvRect.width);
    }*/
}

// Proper Animation
void Animation::Update(Vector2i start, Vector2i finish, float deltaTime, bool faceRight) {
    if (!enabled) {
        return;
    }

    Vector2u startU(imageCount);
    startU.x = start.x;
    startU.y = start.y;
    Vector2u finishU(imageCount);
    finishU.x = finish.x + 1;
    finishU.y = finish.y + 1;
    
    if (!freezeFrame) {
        totalTime += deltaTime;
        if (totalTime >= frameTime) { //Change Frame
            totalTime -= frameTime;
            currentImage.x++;
            if (start.y == finish.y) {
                if (currentImage.x >= finishU.x) {
                    currentImage.x = start.x;
                }
                currentImage.y = start.y;
            }
            else {
                

                if (currentImage.x >= finishU.x) {
                    currentImage.y++;
                    if (currentImage.y >= finishU.y) {
                        currentImage.x = start.x;
                        currentImage.y = start.y;
                    }
                    else {
                        currentImage.x = 0;
                    }
                }
            }
            
        }
        uvRect.top = currentImage.y * uvRect.height;
    }

    /*if (faceRight) {
        uvRect.left = currentImage.x * uvRect.width;
        uvRect.width = abs(uvRect.width);
        cout << "R";
    }
    else {
        uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
        uvRect.width = -abs(uvRect.width);
        cout << "L";
    }*/
}

bool Animation::Update(float deltaTime) {
    if (!enabled) {
        return false;
    }
    bool changedFrame = false;
    //cout << deltaTime << endl;
    Vector2i start = startFrame;
    Vector2i finish = finishFrame;

    Vector2u startU(imageCount);
    startU.x = start.x;
    startU.y = start.y;
    Vector2u finishU(imageCount);
    finishU.x = finish.x + 1;
    finishU.y = finish.y + 1;

    if (!freezeFrame) {
        totalTime += deltaTime;
        if (totalTime >= frameTime) { //Change Frame
            //cout << "CHANGE FRAME" << endl;
            totalTime -= frameTime;
            currentImage.x++;
            if (start.y == finish.y) {
                if (currentImage.x >= finishU.x) {
                    currentImage.x = start.x;
                }
                currentImage.y = start.y;
            }
            else {
                if (currentImage.x >= finishU.x) {
                    currentImage.y++;
                    if (currentImage.y >= finishU.y) {
                        currentImage.x = start.x;
                        currentImage.y = start.y;
                    }
                    else {
                        currentImage.x = 0;
                    }
                }
            }
            changedFrame = true;
        }
        uvRect.left = currentImage.x * uvRect.width;
        uvRect.top = currentImage.y * uvRect.height;
    }

    return changedFrame;
}


void Animation::SetFrameTime(float frameTime) {
    this->frameTime = frameTime;
}
void Animation::SetTexture(Texture* texture) {
    
}
void Animation::SetFrame(Vector2i imageCoordinate) {
    currentImage.x = imageCoordinate.x;
    currentImage.y = imageCoordinate.y;
    uvRect.left = currentImage.x * uvRect.width;
    uvRect.top = currentImage.y * uvRect.height;
}
void Animation::SetFrame(int x, int y) {
    currentImage.x = x;
    currentImage.y = y;
    uvRect.left = currentImage.x * uvRect.width;
    uvRect.top = currentImage.y * uvRect.height;
}
void Animation::SetStartFrame(Vector2i start) {
    if (start.y > finishFrame.y ||
        (start.y == finishFrame.y && start.x > finishFrame.x)) {
        cout << "Error: startFrame can't be more that finishFrame" << endl;
        return;
    }
    
    startFrame = start;
}
void Animation::SetStartFrame(int x, int y) {
    if (y > finishFrame.y ||
        (y == finishFrame.y && x > finishFrame.x)) {
        cout << "Error: startFrame can't be more that finishFrame" << endl;
        return;
    }

    startFrame = Vector2i(x,y);
}
void Animation::SetFinishFrame(Vector2i finish) {
    if (startFrame.y > finish.y ||
        (startFrame.y == finish.y && startFrame.x > finish.x)) {
        cout << "Error: finishFrame can't be less that startFrame" << endl;
        return;
    }

    finishFrame = finish;
}
void Animation::SetFinishFrame(int x, int y) {
    if (startFrame.y > y ||
        (startFrame.y == y && startFrame.x > x)) {
        cout << "Error: finishFrame can't be less that startFrame" << endl;
        return;
    }

    finishFrame = Vector2i(x,y);
}
void Animation::SetStartFinishFrame(int sx, int sy, int fx, int fy) {
    if (sy > fy ||
        (sy == fy && sx > fx)) {
        cout << "Error: startFrame can't be more that finishFrame" << endl;
        return;
    }
    

    startFrame = Vector2i(sx, sy);
    finishFrame = Vector2i(fx, fy);
}
void Animation::SetImageCount(Texture& texture,Vector2u imageCount) {
    this->imageCount = imageCount;

    uvRect.width = texture.getSize().x / float(imageCount.x);
    uvRect.height = texture.getSize().y / float(imageCount.y);
}