#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <unordered_map>
#include <set>
#include <utility>
#include <cmath>
#include <chrono>
#include <ctime>  
#include <fstream>
#include <algorithm>
#include "Animation.h"
#include "GameObject.h"
#include "GravityObject.h"
#include "Pet.h"
#include "PlatformObject.h"
#include "Item.h"
#include "Button.h"
#include "Shop.h"
#include "ParticleSystem.h"
#include "Doodle.h"
#include "Poop.h"
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
using std::sort;

bool CompareDrawLayer(GameObject*& x, GameObject*& y);


class Game
{
public:

    Game();
    Game(RenderWindow& mainWindow);
    ~Game();

    void StartProgram();

    void LoadPetEgg();
    void LoadGame();
    void SaveGame();
    void ClearSave();

    void StartGameLoop();
    void ReInitialize();
    void GetInput();
    void Update();
    void Draw();

    void ReInitializeUI();
    void UpdateUI();
    void DrawUI(RenderWindow& window);


    bool CheckPoopIntegrity(int index); //Returns true if poop should be deleted
    void DeletePoop(int index);
    void DeleteParticle(int index);
    void SetTextUI(Text& text, string str, Font& font, Color color, int size, Vector2f position = Vector2f(720/2,1040/2));
    void SetTextAlignment(Text& text, float anchorPositionX, int alignment); // alignment: 0 = left, 1 = right, 2 = middle

    void CheckKeyPressRelease(unordered_map<string, bool> *keyFlag);
    void CheckKeyPressRelease(unordered_map<string, bool>* keyFlag, Event* evnt);
    void CheckMousePressRelease(unordered_map <string, bool>* mouseFlag);
    void CheckMousePressRelease(unordered_map <string, bool>* mouseFlag, Event* evnt);

    void ResetKeyboard();
    void ResetMouse();

    void PlaySound(Sound& soundPlayer, int soundBufferIndex, string type = "BGM");


    
   
    /// Pet
    Pet* pet;
    vector<Poop*> poops;
    // First time playing
    bool isFirstTimePlaying = false;
    int selectedPet = -1;
    vector<Button*> petEggs;
    vector<string> petEggType = {"PERRY", "DICKO", "CROK", "GYOZA" };
    vector<string> petEggDescriptions = 
    {   petEggType[0] + " is a super ordinary, balanced, normal, whatever you say that means 'basic' pet.",
        petEggType[1] + " likes to eat....I mean it would probably.",
        "In a game where picking up shit gives money, " + petEggType[2] + " is the money maker.",
        "If you want to speed run this game, "+ petEggType[3] + " is for you. Beware this pet is super fragile."};
    Text petEggDescription;

    /// User Interface
    GameObject* mouseCursor;

    Color col_BLACK1 = Color(24, 20, 37);
    Color col_RED1 = Color(244, 4, 69);
    Color col_GREEN1 = Color(99, 199, 77);
    Color col_BROWN1 = Color(184, 111, 80);
    Color col_YELLOW1 = Color(254, 231, 97);
    float ui_barWidth = 210;
    float ui_barHeight = 30;
    float ui_expBarWidth = 410;
    float ui_expBarHeight = 30;
    float ui_happinessBarWidth = 18;
    float ui_happinessBarMaxHeight = 104;
    float ui_happinessBarHeight = 0;
    float ui_happinessBarFloorLevel = 147;
    GameObject* ui_topPanel_front;
    GameObject* ui_topPanel_back;
    GameObject* ui_hpBar;
    GameObject* ui_foodBar;
    GameObject* ui_poopBar;
    GameObject* ui_expBar;
    GameObject* ui_happinessBar;
    GameObject* ui_emotionIcon;
    int emotionFrame = 0;

    Text ui_hpText;
    Text ui_hpMax;
    Text ui_currentHp;
    Text ui_foodText;
    Text ui_foodMax;
    Text ui_currentFood;
    Text ui_poopText;
    Text ui_poopMax;
    Text ui_currentPoop;
    Text ui_expText;
    Text ui_expMax;
    Text ui_currentExp;

    Text ui_money;
    Text ui_levelText;
    Text ui_currentLevel;

    /// Pet
    Button* evolveButton;

    /// Shop
    Shop* shop;
    Button* shopBut;
    vector<Button> buyBut;
    Button* maindishBut;
    Button* dessertBut;
    Button* etcBut;

    /// Minigames
    Button* miniBut;
    Button* startBut;
    Button* exitdoodleBut;
    Button* chooseBut;
    Button* leftBut;
    Button* rightBut;
    Button* backBut;
    Button* selectBut;
    Doodle* doodle;


    ///Sound
    Sound bgm;
    int currentBgm = 0;
    struct SoundVariables {
        string filePath = "";
        float volume = 15.0f;
    };
    float bgmVolume = 12;
    vector<SoundBuffer> bgmSoundBuffers;
    vector<SoundVariables> bgmVariables = {
        {"Assets/Sounds/BGM/bgm_mysticforest.wav", bgmVolume },
        {"Assets/Sounds/BGM/bgm_alonelycherrytree.wav", bgmVolume },
        {"Assets/Sounds/BGM/bgm_mybestfriendisadog.wav", bgmVolume }
        //{"Assets/Sounds/BGM/bgm_otherworld.wav", bgmVolume }
    };
    vector<Sound> sfx;
    vector<SoundBuffer> sfxSoundBuffers;
    float sfxVolume = 15;
    vector<SoundVariables> sfxVariables = {
        {"Assets/Sounds/Pickup_Coin.wav", sfxVolume}
    };
    Sound startProgramSound;
    SoundBuffer startProgramSoundBuffer;
    
    /// ParticleSystem
    vector<ParticleSystem*> particleSystems;

    /// Miscellaneous
    Button* exitBut;
    Button* resetBut;
    Button* mutebgmBut;
    Button* mutesfxBut;
    Game* game;
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

    float pressAnyKeyToStartBlinkTime = 1.5f; //x seconds;
    float pressAnyKeyToStartBlinkTotalTime = 0;
    bool pressAnyKeyToStartIsShown = false;
    Text pressAnyKeyToStartText;

    vector<Font> fonts;
    float fps = 0;
    Text fpsText;
    

    /// System variables
    bool muteBgm = false;
    bool muteSfx = false;

    bool clearSave = false;
    bool quitGame = false;

    int gameState = 0; //0 = start screen, 1 = main game + shop, 2 = doodle jump, -1 = first time playing
    
    int windowWidth = 720;
    int windowHeight = 1040;
    int frameRateLimit = 60;
    string title =  "Tamagotchi";
    
    RenderWindow& window;

    Shader shader;
    
    Clock clock;
    float deltaTime = 0.0f;

    

    /// Input variables
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

