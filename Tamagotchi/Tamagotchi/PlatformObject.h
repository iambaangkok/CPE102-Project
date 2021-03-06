#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include <vector>

using namespace std;
using namespace sf;

class PlatformObject
{
public : 
    PlatformObject(Vector2f size , Vector2i window, int NO_OF_PLATFORM , string filepath);
    ~PlatformObject();

    void Reset();
    void Draw(RenderWindow& window , int difficulty);

    Texture platformtexture;
    GameObject platform;
    vector<Vector2f> platformPos;
    vector<bool> enabled , pass;
    int NO_OF_PLATFORM;
    int prev = 0;
    Vector2i windowSize;
    Vector2f size;

};

