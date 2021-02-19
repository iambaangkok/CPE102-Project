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
    Animation(Texture* texture, Vector2u imageCount, float frameTime = 0.0f);
    ~Animation();

    void Update(int row, float deltaTime, bool faceRight = true);//1Row Animation
    void Update(Vector2i start, Vector2i finish,float deltaTime,bool faceRight = true);//Proper Animation
    void Update(float deltaTime);

    void SetFrameTime(float frameTime);
    void SetTexture(Texture* texture);
    void SetFrame(Vector2i imageCoordinate);
    void SetStartFrame(Vector2i start);
    void SetFinishFrame(Vector2i finish);
    void SetImageCount(Texture& texture,Vector2u imageCount);
    bool enabled = true;
    bool freezeFrame = false;

    IntRect uvRect;
    float frameTime;
    
    Vector2i startFrame = Vector2i(0, 0);
    Vector2i finishFrame = Vector2i(100,100);

private:
    Vector2u imageCount;
    Vector2u currentImage;


    float totalTime;
};