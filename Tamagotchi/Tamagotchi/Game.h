#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <unordered_map>
#include <set>
#include <utility>
#include <cmath>
#include "Animation.h"
#include "GameObject.h"
#include "GravityObject.h"
#include "Pet.h"
#include "PlatformObject.h"
#include "Item.h"
#include "Button.h"
#include "Shop.h"
#include "ParticleSystem.h"
class Button;
class Shop;
class Button;
using namespace sf;

using std::vector;
using std::map;
using std::unordered_map;
using std::pair;
using std::cout;
using std::endl;

class Game
{
public:

    Game();
    Game(RenderWindow& mainWindow);
    ~Game();

    void LoadGame();
    void StartGameLoop();
    void ReInitialize();
    void GetInput();
    void Update();
    void Draw();

    void CheckKeyPressRelease(unordered_map<string, bool> *keyFlag);
    void CheckMousePressRelease(unordered_map <string, bool>* mouseFlag);
    void CheckMousePressRelease(unordered_map <string, bool>* mouseFlag, Event* evnt);

    void ResetKeyboard();
    void ResetMouse();
    
    ParticleSystem* test1;
   

    Pet* pet;

    Shop* shop;
    Button* shopBut;
    Button* miniBut;

    int currentBackground = 0;
    vector<GameObject> backgrounds;

    float cloudSpeed = 80;
    float cloudGap = 400;
    float cloudPosY = 350;
    vector<GameObject> clouds;

    float titlePanelSpeed = 500;//150;
    float titlePanelWidth = 610;
    float titlePanelGap = 70;
    float titlePanelHeight = ceil((float)(titlePanelWidth * 250 / 640)/10) * 10;
    GameObject* titlePanel;

    vector<Font> fonts;

    float fps = 0;
    Text fpsText;

    float pressAnyKeyToStartBlinkTime = 1.5f; //x seconds;
    float pressAnyKeyToStartBlinkTotalTime = 0;
    bool pressAnyKeyToStartIsShown = false;
    Text pressAnyKeyToStartText;
    

    int gameState = 0; //0 = start screen, 1 = main game + shop, 2 = doodle jump
    

    int windowWidth = 720;
    int windowHeight = 1040;
    int frameRateLimit = 60;
    string title =  "Tamagotchi";
    
    RenderWindow& window;
// (VideoMode(windowWidth, windowHeight), title, Style::Close | Style::Resize | Style::Titlebar);
    //RenderWindow& window;
    //VideoMode(windowWidth, windowHeight), title, Style::Close | Style::Titlebar | Style::Resize
    float deltaTime = 0.0f;
    Clock clock;

    Event evnt;

    Vector2i mousePosition = Vector2i(0, 0);
    int mouseWheelDelta = 0;

    bool anyKeyPressed = false;
    bool anyMousePressed = false;
    
    unordered_map<string, bool> keyPress = { //1 Only when the first frame that the key is pressed
        {"W",0},{"A",0},{"S",0},{"D",0},
        {"SPACE",0},{"LSHIFT",0},{"LCTRL",0},
        {"ENTER",0},{"ESC",0},{"TAB",0},
        {"Q",0},{"E",0},{"R",0},{"T",0},
        {"F",0},{"G",0},
        {"Z",0},{"X",0},{"C",0},{"V",0},
    };
    unordered_map<string, bool> keyRelease = { //1 Only when the frame that the key is released
        {"W",0},{"A",0},{"S",0},{"D",0},
        {"SPACE",0},{"LSHIFT",0},{"LCTRL",0},
        {"ENTER",0},{"ESC",0},{"TAB",0},
        {"Q",0},{"E",0},{"R",0},{"T",0},
        {"F",0},{"G",0},
        {"Z",0},{"X",0},{"C",0},{"V",0},
    };
    unordered_map<string, bool> keyHold = { //1 as long as the key is down
        {"W",0},{"A",0},{"S",0},{"D",0},
        {"SPACE",0},{"LSHIFT",0},{"LCTRL",0},
        {"ENTER",0},{"ESC",0},{"TAB",0},
        {"Q",0},{"E",0},{"R",0},{"T",0},
        {"F",0},{"G",0},
        {"Z",0},{"X",0},{"C",0},{"V",0},
    };

    unordered_map<string, bool> mousePress = {
        {"M1",0},{"M2",0},{"M3",0},
    };

    unordered_map<string, bool> mouseRelease = {
        {"M1",0},{"M2",0},{"M3",0},
    };

    unordered_map<string, bool> mouseHold = {
        {"M1",0},{"M2",0},{"M3",0},
    };

    
};

