#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using std::cout;
using std::endl;

class Animation
{
public:
    Animation();
    Animation(Texture* texture, Vector2u imageCount, float frameTime);
    ~Animation();

    void Update(int row, float deltaTime, bool faceRight);
    void SetFrameTime(float frameTime);
    void SetTexture(Texture* texture);
    void SetFrame(Vector2u rowColumn);
    
    bool enabled = true;
    bool freezeFrame = false;

    IntRect uvRect;
    float frameTime;
    

private:
    Vector2u imageCount;
    Vector2u currentImage;

    float totalTime;
};