#pragma once
#include "GameObject.h"

class GravityObject
{   
public :
    GravityObject(Vector2f position, Vector2f dimensions, float Height , string filepath);
    ~GravityObject();

    bool CheckCollision(Vector2f otherPos , Vector2f otherHalfSize);

    GameObject player;
    Texture playertexture;

    float dy = 0;
    float Height;
    float playerX, playerY;
private :



};

