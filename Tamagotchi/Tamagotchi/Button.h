#pragma once
#include "GameObject.h"
#include "Game.h"
#include "Shop.h"
#include "Pet.h"
#include "Doodle.h"
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
        , string text, int status, string type, int& gstate, Shop& shop, Pet& pet,Doodle &doodle, int id = -69); //Proper Animation
    ~Button();

    void Initialize();//Runs before everything else in every game loop/ reset variable that needs to be reset every game loop

    void Update(float deltaTime,RenderWindow& window,unordered_map<string, bool>& mousePress, unordered_map<string, bool>& mouseHold, Vector2i& mousePosition, bool& quitGame, int& selectedPet, bool& clearSave, bool& muteBgm, bool& muteSfx);

    

    void OnClick(bool& muteBgm, bool& muteSfx);
    void OnHover();
    void OnHold();
    void OnRelease(bool& quitGame, int& selectedPet, bool& clearSave);
    bool IsMouseOver(Vector2i& mousePosition);


    string text;
    int status; // 0:default,1:mousehover,2:clicked,3:clicked and hover,4:unavalible
    int prevstatus = -1;
    string type;
    int* gstate;
    Shop* shop;
    Pet* pet;
    Doodle* doodle;
    bool isPressed = false;
    int id;
};

