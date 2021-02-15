#pragma once
#include "GameObject.h"
class GravityObject :
    public GameObject
{   
public :
    GravityObject(Vector2f position, Vector2f dimensions, float speed , float jumpHeight);
    ~GravityObject();

    void Update(float deltaTime);
    void OnCollision(Vector2f direction);

    Vector2f velocity;
    float speed;
    float jumpHeight;
    bool canJump;
    bool doodleEnabled = false;

private :



};

