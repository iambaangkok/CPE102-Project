#pragma once
#include "GameObject.h"

class GravityObject
{   
public :
    GravityObject(Vector2f position, Vector2f dimensions, float Height , string filepath , int curlevel);
    ~GravityObject();

    void Update(float deltaTime , float speed_rate);
    bool CheckCollision(Vector2f otherPos , Vector2f otherHalfSize);

    GameObject player;
    Texture playertexture;
    int curlevel = 0;

    float dy = 0;
    float Height;
    float playerX, playerY;
private :



};

