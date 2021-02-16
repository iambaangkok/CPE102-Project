#pragma once
#include "GameObject.h"
#include "Game.h"
#include <vector>
using std::vector;
class Game;
class Button :
    public GameObject
{
public: 
    Button();
    Button(Vector2f position, Vector2f dimensions, bool originIsCenter,
        string texturePath, Vector2u imageCount, Vector2i start, Vector2i finish, float frameTime
        ,vector<Color> color,string text,int status,string type); //Proper Animation
    ~Button();

    void Initialize();//Runs before everything else in every game loop/ reset variable that needs to be reset every game loop

    void Update(float deltaTime,RenderWindow& window,unordered_map<string, bool>& mousePress);

    vector<Color> color;
    string text;
    int status; // 0:default,1:mousehover,2:clicked,3:unavalible
    string type;
};

