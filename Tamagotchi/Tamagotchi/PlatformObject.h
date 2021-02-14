#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include <vector>

using namespace std;
using namespace sf;

class PlatformObject
{
public : 
    PlatformObject(Vector2f size , Vector2i window, int NO_OF_PLATFORM);
    ~PlatformObject();


    void Initialize();
    void Update();
    void Draw(RenderWindow& window);

    vector<GameObject> platform;
    int NO_OF_PLATFORM;
    Vector2i windowSize;
    Vector2f size;

};

