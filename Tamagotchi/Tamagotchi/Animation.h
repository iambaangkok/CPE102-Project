#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Animation
{
public:
    Animation();
    Animation(Texture* texture, Vector2u imageCount, float frameTime);
    ~Animation();

    void Update(int row, float deltaTime, bool faceRight);
    void SetFrameTime(float frameTime);
    void SetTexture(Texture* texture);
    void SetFrame(int row, int column, bool faceRight);
    
    bool enabled = true;

    IntRect uvRect;
    float frameTime;
    

private:
    Vector2u imageCount;
    Vector2u currentImage;

    float totalTime;
};