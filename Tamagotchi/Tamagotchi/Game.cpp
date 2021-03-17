#include "Game.h"

bool CompareDrawLayer(GameObject*& x, GameObject*& y) {
    return x->drawLayer < y->drawLayer;
}


Game::Game(RenderWindow& mainWindow) : window(mainWindow){

	window.setFramerateLimit(frameRateLimit);  
	deltaTime = 0;
	clock.restart();
    if (Shader::isAvailable()) {
        //shader.loadFromFile("vertex_shader.shader", "fragment_shader.shader");
    }
}

Game::~Game() {

}

void Game::StartProgram() {
    GameObject startProgram(Vector2f(0, 0), Vector2f(windowWidth, windowHeight), false, "Assets/Textures/startprogram.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 1);
    startProgram.Draw(window);
    window.display();
    startProgramSoundBuffer.loadFromFile("Assets/Sounds/startprogram.wav");
    startProgramSound = Sound(startProgramSoundBuffer);
    startProgramSound.setVolume(25);
    startProgramSound.play();
}

void Game::LoadPetEgg() {
    cout << "First Time Playing " << endl;
    float petEggPosX = 70;
    float petEggDimX = 130;
    float petEggGapX = 20;
    float petEggPosY = 300;
    static Button petEgg1 = Button(Vector2f(petEggPosX + (petEggs.size()) * petEggDimX + (petEggs.size()) * petEggGapX, petEggPosY), Vector2f(petEggDimX, 140), false,
        "Assets/Textures/button_petEgg_01_x2.png", Vector2u(5, 1), Vector2i(0, 0), Vector2i(0, 0), 1
        , petEggType[petEggs.size()], 0, "PETEGG", gameState, *shop, *pet, *doodle, 0);
    petEgg1.animation.freezeFrame = true;
    petEggs.push_back(&petEgg1);
    static Button petEgg2 = Button(Vector2f(petEggPosX + (petEggs.size()) * petEggDimX + (petEggs.size()) * petEggGapX, petEggPosY), Vector2f(petEggDimX, 140), false,
        "Assets/Textures/button_petEgg_02_x2.png", Vector2u(5, 1), Vector2i(0, 0), Vector2i(0, 0), 1
        , petEggType[petEggs.size()], 0, "PETEGG", gameState, *shop, *pet, *doodle, 1);
    petEgg2.animation.freezeFrame = true;
    petEggs.push_back(&petEgg2);
    static Button petEgg3 = Button(Vector2f(petEggPosX + (petEggs.size()) * petEggDimX + (petEggs.size()) * petEggGapX, petEggPosY), Vector2f(petEggDimX, 140), false,
        "Assets/Textures/button_petEgg_03_x2.png", Vector2u(5, 1), Vector2i(0, 0), Vector2i(0, 0), 1
        , petEggType[petEggs.size()], 0, "PETEGG", gameState, *shop, *pet, *doodle, 2);
    petEgg3.animation.freezeFrame = true;
    petEggs.push_back(&petEgg3);
    static Button petEgg4 = Button(Vector2f(petEggPosX + (petEggs.size()) * petEggDimX + (petEggs.size()) * petEggGapX, petEggPosY), Vector2f(petEggDimX, 140), false,
        "Assets/Textures/button_petEgg_04_x2.png", Vector2u(5, 1), Vector2i(0, 0), Vector2i(0, 0), 1
        , petEggType[petEggs.size()], 0, "PETEGG", gameState, *shop, *pet, *doodle, 3);
    petEgg4.animation.freezeFrame = true;
    petEggs.push_back(&petEgg4);

    //gameState = -1;
    isFirstTimePlaying = true;
}

void Game::LoadGame() {
    Font font1;
    if (!font1.loadFromFile("Assets/Fonts/Minecraftia.ttf"))
        throw("COULD NOT LOAD FONT! ");
    fonts.push_back(font1);

    ifstream saveFile("Savefiles/save001.sav");
    string textline = "";
    string format = "";
    string blankStr = "";
    long long int nLine = 1;
    if ((!getline(saveFile, textline) && selectedPet == -1 )) { //First time playing 
        LoadPetEgg();
    }    
    else  {
        nLine++;
        cout << textline << endl;

        string name = "Unset Name";
        string type = "Unset Type";
        string texturePath = "Assets/Textures/";
        float grassFieldTopBorder = 560;
        float grassFieldHeight = 730 - 560;
        float grassFieldThickness = 1000;
        float playerSize = 160.0f;

        if (selectedPet == -1 && !isFirstTimePlaying) {
            cout << "Loading Save Data..." << endl;
            /// Pet
            getline(saveFile, textline); nLine++;
            name = textline.substr(5, textline.size() - 5);

            getline(saveFile, textline); nLine++;
            type = textline.substr(5, textline.size() - 5);

            cout << name << " " << type << endl;

            float playerSize = 160.0f;
            if (type == "PERRY") {
                texturePath += "pet_01_x2.png";
            }
            else if (type == "DICKO") {
                texturePath += "pet_02_x2.png";
            }
            else if (type == "CROK") {
                texturePath += "pet_03.png";
            }
            else if (type == "GYOZA") {
                texturePath += "pet_04.png";
            }
            else {
                cout << "Invalid Pet Type." << endl;
                window.close();
            }

            static Pet p = Pet(Vector2f((float)(windowWidth / 2), (float)(windowHeight / 2)), Vector2f(playerSize, playerSize), true,
                texturePath, Vector2u(5, 3), Vector2i(1, 0), Vector2i(2, 0), 0.3f,
                name, type);
            pet = &p;

            getline(saveFile, textline); nLine++;
            format = "time_sinceBirth %ld";
            sscanf_s(textline.c_str(), format.c_str(), &(pet->time_sinceBirth)); //READ FROM FILE ONCE
            getline(saveFile, textline); nLine++;
            format = "time_lastSession %ld";
            sscanf_s(textline.c_str(), format.c_str(), &(pet->time_lastSession)); //READ FROM FILE ONCE
            pet->time_currentTime_sinceEpoch = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count(); //Update every frame
            pet->time_sinceLastSession = pet->time_currentTime_sinceEpoch - pet->time_lastSession; //Calculate once at start
            pet->time_currentSession = pet->time_currentTime_sinceEpoch - pet->time_lastSession; //Update every frame
            pet->time_alive = pet->time_currentTime_sinceEpoch - pet->time_sinceBirth; //READ FROM FILE ONCE & Update every frame
            /*const auto p0 = std::chrono::time_point<std::chrono::system_clock>{};
            const auto p1 = std::chrono::system_clock::now();
            std::time_t epochTime = std::chrono::system_clock::to_time_t(p0);
            std::cout << "seconds since epoch: " << std::chrono::duration_cast<std::chrono::seconds>(p1.time_since_epoch()).count()<< '\n';
            const auto p2 = p1 - std::chrono::hours(24);
            std::cout << "yesterday, hours since epoch: "<< std::chrono::duration_cast<std::chrono::hours>(p2.time_since_epoch()).count()<< '\n';*/
            getline(saveFile, textline); nLine++;
            format = "level %d";
            sscanf_s(textline.c_str(), format.c_str(), &(pet->currentLevel));
            getline(saveFile, textline); nLine++;
            format = "exp %f";
            sscanf_s(textline.c_str(), format.c_str(), &(pet->currentExp));
            getline(saveFile, textline); nLine++;
            format = "evolveStone %ld"; int ateEvolveStone = 0;
            sscanf_s(textline.c_str(), format.c_str(), &(ateEvolveStone)); pet->ateEvolveStone = ((ateEvolveStone == 1) ? true : false);
            getline(saveFile, textline); nLine++;
            format = "hp %f";
            sscanf_s(textline.c_str(), format.c_str(), &(pet->currentHp));
            getline(saveFile, textline); nLine++;
            format = "happiness %f";
            sscanf_s(textline.c_str(), format.c_str(), &(pet->currentHappiness));
            getline(saveFile, textline); nLine++;
            format = "food %f";
            sscanf_s(textline.c_str(), format.c_str(), &(pet->currentFood));
            getline(saveFile, textline); nLine++;
            format = "poop %f";
            sscanf_s(textline.c_str(), format.c_str(), &(pet->currentPoop));

            static GameObject pShadow = GameObject(Vector2f((float)(windowWidth / 2), (float)(windowHeight / 2)), Vector2f(140, 60), true,
                "Assets/Textures/shadow_01.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 10);
            pet->shadow = &pShadow;


            //1 = right, 2 = left, 3 = bottom, 4 = top
            static GameObject pBorder1 = GameObject(Vector2f(windowWidth + grassFieldThickness / 2, grassFieldTopBorder + grassFieldHeight / 2), Vector2f(grassFieldThickness, grassFieldHeight), true,
                "Assets/Textures/DefaultTexture.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 10);
            static GameObject pBorder2 = GameObject(Vector2f(0 - grassFieldThickness + grassFieldThickness / 2, grassFieldTopBorder + grassFieldHeight / 2), Vector2f(grassFieldThickness, grassFieldHeight), true,
                "Assets/Textures/DefaultTexture.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 10);
            static GameObject pBorder3 = GameObject(Vector2f(windowWidth / 2, grassFieldTopBorder - grassFieldThickness / 2), Vector2f(windowWidth, grassFieldThickness), true,
                "Assets/Textures/DefaultTexture.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 10);
            static GameObject pBorder4 = GameObject(Vector2f(windowWidth / 2, grassFieldTopBorder + grassFieldHeight + grassFieldThickness / 2), Vector2f(windowWidth, grassFieldThickness), true,
                "Assets/Textures/DefaultTexture.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 10);

            pet->shadowBorder.push_back(pBorder1);
            pet->shadowBorder.push_back(pBorder2);
            pet->shadowBorder.push_back(pBorder3);
            pet->shadowBorder.push_back(pBorder4);

        }
        else {
            cout << "Initializing FTP... " << endl;
            /// Pet
            name = petEggType[selectedPet];
            type = name;
            cout << name << " " << type << endl;

            if (type == "PERRY") {
                texturePath += "pet_01_x2.png";
            }
            else if (type == "DICKO") {
                texturePath += "pet_02_x2.png";
            }
            else if (type == "CROK") {
                texturePath += "pet_03.png";
            }
            else if (type == "GYOZA") {
                texturePath += "pet_04.png";
            }
            else {
                cout << "Invalid Pet Type." << endl;
                window.close();
            }

            static Pet p = Pet(Vector2f((float)(windowWidth / 2), (float)(windowHeight / 2)), Vector2f(playerSize, playerSize), true,
                texturePath, Vector2u(5, 3), Vector2i(1, 0), Vector2i(2, 0), 0.3f,
                name, type);
            pet = &p;
            

            pet->time_sinceBirth = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            pet->time_lastSession = pet->time_sinceBirth;
            pet->time_currentTime_sinceEpoch = pet->time_sinceBirth;
            pet->time_sinceLastSession = pet->time_currentTime_sinceEpoch - pet->time_lastSession;
            pet->time_currentSession = pet->time_currentTime_sinceEpoch - pet->time_lastSession;
            pet->time_alive = pet->time_currentTime_sinceEpoch - pet->time_sinceBirth;/*const auto p0 = std::chrono::time_point<std::chrono::system_clock>{};
            const auto p1 = std::chrono::system_clock::now();
            std::time_t epochTime = std::chrono::system_clock::to_time_t(p0);
            std::cout << "seconds since epoch: " << std::chrono::duration_cast<std::chrono::seconds>(p1.time_since_epoch()).count()<< '\n';
            const auto p2 = p1 - std::chrono::hours(24);
            std::cout << "yesterday, hours since epoch: "<< std::chrono::duration_cast<std::chrono::hours>(p2.time_since_epoch()).count()<< '\n';*/
            pet->currentLevel = 0;
            pet->currentExp = 0;
            pet->ateEvolveStone = false;
            pet->currentHp = pet->hpMax[pet->currentLevel];
            pet->currentHappiness = pet->happinessMax[pet->currentLevel];
            pet->currentFood = pet->foodMax[pet->currentLevel];
            pet->currentPoop = pet->poopMax[pet->currentLevel];

            static GameObject pShadow = GameObject(Vector2f((float)(windowWidth / 2), (float)(windowHeight / 2)), Vector2f(140, 60), true,
                "Assets/Textures/shadow_01.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 10);
            pet->shadow = &pShadow;

            //1 = right, 2 = left, 3 = bottom, 4 = top
            static GameObject pBorder1 = GameObject(Vector2f(windowWidth + grassFieldThickness / 2, grassFieldTopBorder + grassFieldHeight / 2), Vector2f(grassFieldThickness, grassFieldHeight), true,
                "Assets/Textures/DefaultTexture.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 10);
            static GameObject pBorder2 = GameObject(Vector2f(0 - grassFieldThickness + grassFieldThickness / 2, grassFieldTopBorder + grassFieldHeight / 2), Vector2f(grassFieldThickness, grassFieldHeight), true,
                "Assets/Textures/DefaultTexture.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 10);
            static GameObject pBorder3 = GameObject(Vector2f(windowWidth / 2, grassFieldTopBorder - grassFieldThickness / 2), Vector2f(windowWidth, grassFieldThickness), true,
                "Assets/Textures/DefaultTexture.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 10);
            static GameObject pBorder4 = GameObject(Vector2f(windowWidth / 2, grassFieldTopBorder + grassFieldHeight + grassFieldThickness / 2), Vector2f(windowWidth, grassFieldThickness), true,
                "Assets/Textures/DefaultTexture.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 10);

            pet->shadowBorder.push_back(pBorder1);
            pet->shadowBorder.push_back(pBorder2);
            pet->shadowBorder.push_back(pBorder3);
            pet->shadowBorder.push_back(pBorder4);
        }

    }
    saveFile.close();

    if (pet != NULL) {
        cout << "Loading User Interface..." << endl;
        /// User Interface
        static GameObject ui_tp_f = GameObject(Vector2f(0, 0), Vector2f(windowWidth, 200), false, "Assets/Textures/panel_top_x3_front.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 10);
        ui_topPanel_front = &ui_tp_f;

        static GameObject ui_tp_b = GameObject(Vector2f(0, 0), Vector2f(windowWidth, 200), false, "Assets/Textures/panel_top_x3_back.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 10);
        ui_topPanel_back = &ui_tp_b;

        static GameObject ui_hpb = GameObject(Vector2f(90, 40), Vector2f((float)pet->currentHp / pet->hpMax[pet->currentLevel] * ui_barWidth, ui_barHeight), false,
            "Assets/Textures/panel_top_x3_hpBar.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 10);
        ui_hpBar = &ui_hpb;
        static GameObject ui_fb = GameObject(Vector2f(90, 80), Vector2f((float)pet->currentFood / pet->foodMax[pet->currentLevel] * ui_barWidth, ui_barHeight), false,
            "Assets/Textures/panel_top_x3_foodBar.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 10);
        ui_foodBar = &ui_fb;
        static GameObject ui_pb = GameObject(Vector2f(90, 120), Vector2f((float)pet->currentPoop / pet->poopMax[pet->currentLevel] * ui_barWidth, ui_barHeight), false,
            "Assets/Textures/panel_top_x3_poopBar.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 10);
        ui_poopBar = &ui_pb;

        static GameObject ui_expb = GameObject(Vector2f(90, 160), Vector2f((float)pet->currentExp / pet->expPerEvolve[pet->currentLevel] * ui_expBarWidth, ui_expBarHeight), false,
            "Assets/Textures/panel_top_x3_expBar.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 10);
        ui_expBar = &ui_expb;

        ui_happinessBarHeight = (float)pet->currentHappiness / pet->happinessMax[pet->currentLevel] * ui_happinessBarMaxHeight;
        static GameObject ui_hab = GameObject(Vector2f(400, ui_happinessBarFloorLevel - ui_happinessBarHeight), Vector2f(ui_happinessBarWidth, ui_happinessBarHeight), false, Color(255, 255, 255));
        ui_happinessBar = &ui_hab;
        static GameObject ui_emoico = GameObject(Vector2f(450, 40), Vector2f(110, 110), false, "Assets/Textures/panel_top_x3_emotionIcon.png", Vector2u(5, 1), Vector2i(0, 0), Vector2i(0, 0), 1);
        ui_emotionIcon = &ui_emoico;
        ui_emotionIcon->animation.freezeFrame = true;
        emotionFrame = 0;
        ui_emotionIcon->SetFrame(emotionFrame, 0);

        //SetTextUI(ui_hpText, "HP", fonts[0], col_BLACK1, 20, Vector2f(40, 40));

        float gapXPlus = 20;
        float gapXMinus = 10;

        float fontSize = 14;
        SetTextUI(ui_hpMax, "/" + to_string(pet->hpMax[pet->currentLevel]), fonts[0], col_BLACK1, fontSize, Vector2f(335 + gapXPlus - 5, 60));
        SetTextUI(ui_currentHp, to_string(pet->currentHp), fonts[0], col_BLACK1, fontSize - 2, Vector2f(335 - gapXMinus, 50));

        //SetTextUI(ui_foodText, "FOOD", fonts[0], col_BLACK1, 20, Vector2f(40, 80));
        SetTextUI(ui_foodMax, "/" + to_string(pet->foodMax[pet->currentLevel]), fonts[0], col_BLACK1, fontSize, Vector2f(330 + gapXPlus, 100));
        SetTextUI(ui_currentFood, to_string(pet->currentFood), fonts[0], col_BLACK1, fontSize - 2, Vector2f(335 - gapXMinus, 90));

        //SetTextUI(ui_poopText, "POO", fonts[0], col_BLACK1, 20, Vector2f(40, 120));
        SetTextUI(ui_poopMax, "/" + to_string(pet->poopMax[pet->currentLevel]), fonts[0], col_BLACK1, fontSize, Vector2f(330 + gapXPlus, 140));
        SetTextUI(ui_currentPoop, to_string(pet->currentPoop), fonts[0], col_BLACK1, fontSize - 2, Vector2f(335 - gapXMinus, 130));

        //SetTextUI(ui_expText, "EXP", fonts[0], col_BLACK1, 20, Vector2f(40, 160));
        SetTextUI(ui_expMax, "/" + to_string(pet->expPerEvolve[pet->currentLevel]), fonts[0], col_BLACK1, fontSize, Vector2f(520 + gapXPlus - 5, 180));
        SetTextUI(ui_currentExp, to_string(pet->currentExp), fonts[0], col_BLACK1, fontSize - 2, Vector2f(520 - gapXMinus + 5, 170));

        SetTextUI(ui_money, to_string(pet->currentExp), fonts[0], col_BLACK1, 20, Vector2f(630, 65));
        SetTextUI(ui_levelText, "LEVEL", fonts[0], col_BLACK1, 20, Vector2f(600, 120));
        SetTextUI(ui_currentLevel, to_string(pet->currentLevel + 1), fonts[0], col_BLACK1, 20, Vector2f(635, 140));


        /// Pet
        static Button evB = Button(Vector2f(580, 135), Vector2f(110, 60), false,
            "Assets/Textures/button_evolve.png", Vector2u(5, 1), Vector2i(0, 0), Vector2i(0, 0), 1
            , "evB", 0, "EVOLVE", gameState, *shop, *pet, *doodle);
        evB.animation.freezeFrame = true;
        evolveButton = &evB;

        /// Shop
        static Shop s = Shop();
        shop = &s;

        static Button sB = Button(Vector2f(210, 890), Vector2f(130, 140), false,
            "Assets/Textures/button_yellow_01.png", Vector2u(5, 1), Vector2i(0, 0), Vector2i(0, 0), 1
            , "TOGGLE", 0, "SHOP", gameState, *shop, *pet, *doodle);
        sB.animation.freezeFrame = true;
        shopBut = &sB;

        /// Minigames
        static Button mnB = Button(Vector2f(380, 890), Vector2f(130, 140), false,
            "Assets/Textures/button_blue_01.png", Vector2u(5, 1), Vector2i(0, 0), Vector2i(0, 0), 1
            , "mnB", 0, "MINIGAME", gameState, *shop, *pet, *doodle);
        mnB.animation.freezeFrame = true;
        miniBut = &mnB;

        static Doodle d = Doodle(gameState, *pet);
        doodle = &d;

        /// BuyItems
        for (int i = 0; i < 18; ++i) {
            static Button bB = Button(Vector2f(380, 890), Vector2f(130, 140), false,
                "Assets/Textures/button_buy.png", Vector2u(5, 1), Vector2i(0, 0), Vector2i(0, 0), 1
                , "bB", 0, "BUYITEM", gameState, *shop, *pet, *doodle, i + 1);
            bB.animation.freezeFrame = true;
            buyBut.push_back(bB);
        }

        static Button mdB = Button(Vector2f(310, 200), Vector2f(125, 70), false,
            "Assets/Textures/button_food_w80.png", Vector2u(5, 1), Vector2i(0, 0), Vector2i(0, 0), 1
            , "TOGGLE", 0, "MAINDISH", gameState, *shop, *pet, *doodle);
        mdB.animation.freezeFrame = true;
        maindishBut = &mdB;

        static Button dsB = Button(Vector2f(435, 200), Vector2f(155, 70), false,
            "Assets/Textures/button_candy_w80.png", Vector2u(5, 1), Vector2i(0, 0), Vector2i(0, 0), 1
            , "TOGGLE", 0, "DESSERT", gameState, *shop, *pet, *doodle);
        dsB.animation.freezeFrame = true;
        dessertBut = &dsB;

        static Button etcB = Button(Vector2f(585, 200), Vector2f(125, 70), false,
            "Assets/Textures/button_etc_w80.png", Vector2u(5, 1), Vector2i(0, 0), Vector2i(0, 0), 1
            , "TOGGLE", 0, "ETC", gameState, *shop, *pet, *doodle);
        etcB.animation.freezeFrame = true;
        etcBut = &etcB;

        /// Doodle
        static Button stB = Button(Vector2f(210, 890), Vector2f(130, 140), false,
            "Assets/Textures/button_yellow_01.png", Vector2u(5, 1), Vector2i(0, 0), Vector2i(0, 0), 1
            , "stB", 0, "STARTDOODLE", gameState, *shop, *pet, *doodle);
        stB.animation.freezeFrame = true;
        startBut = &stB;

        static Button edB = Button(Vector2f(210, 890), Vector2f(130, 140), false,
            "Assets/Textures/button_yellow_01.png", Vector2u(5, 1), Vector2i(0, 0), Vector2i(0, 0), 1
            , "edB", 0, "EXITDOODLE", gameState, *shop, *pet, *doodle);
        edB.animation.freezeFrame = true;
        exitdoodleBut = &edB;

        static Button cbgB = Button(Vector2f(210, 890), Vector2f(130, 140), false,
            "Assets/Textures/button_yellow_01.png", Vector2u(5, 1), Vector2i(0, 0), Vector2i(0, 0), 1
            , "cbgB", 0, "CHOOSEBG", gameState, *shop, *pet, *doodle);
        cbgB.animation.freezeFrame = true;
        chooseBut = &cbgB;

        static Button lB = Button(Vector2f(10, 460), Vector2f(130, 140), false,
            "Assets/Textures/button_left.png", Vector2u(5, 1), Vector2i(0, 0), Vector2i(0, 0), 1
            , "lB", 0, "LEFTDOODLE", gameState, *shop, *pet, *doodle);
        lB.animation.freezeFrame = true;
        leftBut = &lB;

        static Button rB = Button(Vector2f(580, 460), Vector2f(130, 140), false,
            "Assets/Textures/button_right.png", Vector2u(5, 1), Vector2i(0, 0), Vector2i(0, 0), 1
            , "rB", 0, "RIGHTDOODLE", gameState, *shop, *pet, *doodle);
        rB.animation.freezeFrame = true;
        rightBut = &rB;

        static Button bacB = Button(Vector2f(210, 890), Vector2f(130, 140), false,
            "Assets/Textures/button_yellow_01.png", Vector2u(5, 1), Vector2i(0, 0), Vector2i(0, 0), 1
            , "bacB", 0, "BACKDOODLE", gameState, *shop, *pet, *doodle);
        bacB.animation.freezeFrame = true;
        backBut = &bacB;

        static Button slB = Button(Vector2f(210, 890), Vector2f(130, 140), false,
            "Assets/Textures/button_yellow_01.png", Vector2u(5, 1), Vector2i(0, 0), Vector2i(0, 0), 1
            , "slB", 0, "SELECTBG", gameState, *shop, *pet, *doodle);
        slB.animation.freezeFrame = true;
        selectBut = &slB;

        /// Miscellaneous
        static Button eB = Button(Vector2f(540, 890), Vector2f(130, 140), false,
            "Assets/Textures/button_red_01.png", Vector2u(5, 1), Vector2i(0, 0), Vector2i(0, 0), 1
            , "eB", 0, "EXIT", gameState, *shop, *pet, *doodle);
        eB.animation.freezeFrame = true;
        exitBut = &eB;

        static Button rsB = Button(Vector2f(670, 996), Vector2f(32, 34), false,
            "Assets/Textures/button_reset.png", Vector2u(5, 1), Vector2i(0, 0), Vector2i(0, 0), 1
            , "rsB", 0, "RESET", gameState, *shop, *pet, *doodle);
        rsB.animation.freezeFrame = true;
        resetBut = &rsB;

        static Button mbgmB = Button(Vector2f(80, 890), Vector2f(65, 70), false,
            "Assets/Textures/button_mutebgm.png", Vector2u(5, 1), Vector2i(0, 0), Vector2i(0, 0), 1
            , "TOGGLE", 0, "MUTEBGM", gameState, *shop, *pet, *doodle);
        mbgmB.animation.freezeFrame = true;
        mutebgmBut = &mbgmB;

        static Button msfxB = Button(Vector2f(80, 960), Vector2f(65, 70), false,
            "Assets/Textures/button_mutesfx.png", Vector2u(5, 1), Vector2i(0, 0), Vector2i(0, 0), 1
            , "TOGGLE", 0, "MUTESFX", gameState, *shop, *pet, *doodle);
        msfxB.animation.freezeFrame = true;
        mutesfxBut = &msfxB;

        static GameObject ypd = GameObject(Vector2f(windowWidth / 2, windowHeight / 2 - 100), Vector2f(590 * 0.8, 290 * 0.8), true, "Assets/Textures/yourpetdied.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 1);
        yourPetDied = &ypd;

    }
    if (selectedPet == -1 || !isFirstTimePlaying) {
        static GameObject mCS = GameObject(Vector2f(0, 0), Vector2f(64, 64), false, "Assets/Textures/mouseCursor.png", Vector2u(4, 1), Vector2i(0, 0), Vector2i(0, 0), 1);
        mouseCursor = &mCS;

        static GameObject bg = GameObject(Vector2f(0, 0), Vector2f(windowWidth, windowHeight), false, "Assets/Textures/BGMain.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 1);
        backgrounds.push_back(bg);

        if (clouds.size() == 0) {
            static GameObject cloud1 = GameObject(Vector2f(0, -10), Vector2f(120, 60), false, "Assets/Textures/clouds_01.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 1);
            static GameObject cloud2 = GameObject(Vector2f(0, +10), Vector2f(200, 80), false, "Assets/Textures/clouds_02.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 1);
            clouds.push_back(cloud1);
            clouds.push_back(cloud2);
            clouds.push_back(cloud1);
            clouds.push_back(cloud2);
            for (int i = 0; i < clouds.size(); ++i) {
                clouds[i].SetPosition(-(i * cloudGap + 120), cloudPosY + clouds[i].GetPosition().y);
            }
        }
        
        static GameObject ti = GameObject(Vector2f(-titlePanelGap - titlePanelWidth - titlePanelGap, 160), Vector2f(titlePanelWidth, titlePanelHeight), false, "Assets/Textures/title_bordered.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 1);
        titlePanel = &ti;

        pressAnyKeyToStartText.setString("Press Any Key to Start");
        pressAnyKeyToStartText.setFont(fonts[0]);
        pressAnyKeyToStartText.setFillColor(Color::White);
        pressAnyKeyToStartText.setCharacterSize(25);
        pressAnyKeyToStartText.setPosition(windowWidth / 2 - 180, titlePanelHeight + 160 + 40);
        pressAnyKeyToStartText.setStyle(Text::Bold);

        fpsText.setString(to_string(fps));
        fpsText.setFont(fonts[0]);
        fpsText.setFillColor(Color::Black);
        fpsText.setCharacterSize(16);
        fpsText.setPosition(windowWidth - 40, 10);
    }

    if (bgmSoundBuffers.size() == 0) {
        bgmSoundBuffers = vector<SoundBuffer>(bgmVariables.size(), SoundBuffer());
        for (int i = 0; i < bgmVariables.size(); ++i) {
            if (bgmSoundBuffers[i].loadFromFile(bgmVariables[i].filePath)) {
                cout << "Loaded BGM " << bgmVariables[i].filePath << endl;
            }
            else {
                cout << "Failed to load BGM " << bgmVariables[i].filePath << endl;
            }
        }
        currentBgm = rand() % bgmVariables.size();
        PlaySound(bgm, currentBgm);
    }
    if (sfxSoundBuffers.size() == 0) {
        sfxSoundBuffers = vector<SoundBuffer>(sfxVariables.size(), SoundBuffer());
        for (int i = 0; i < sfxVariables.size(); ++i) {
            if (sfxSoundBuffers[i].loadFromFile(sfxVariables[i].filePath)) {
                sfx.push_back(Sound(sfxSoundBuffers[i]));
                cout << "Loaded SFX " << sfxVariables[i].filePath << endl;
            }
            else {
                cout << "Failed to load SFX " << sfxVariables[i].filePath << endl;
            }
        }
    }
    
    deltaTime = clock.restart().asSeconds();
}
void Game::SaveGame() {
    ofstream saveFile("Savefiles/save001.sav");
    string textline = "";
    string format = "";
    long long int nLine = 1;
    saveFile << "#Pet" << endl;
    saveFile << "name " << pet->name << endl;
    saveFile << "type " << pet->type << endl;
    saveFile << "time_sinceBirth " << pet->time_sinceBirth << endl;
    saveFile << "time_lastSession " << pet->time_currentTime_sinceEpoch << endl;
    saveFile << "level " << pet->currentLevel << endl;
    saveFile << "exp " << pet->currentExp << endl;
    saveFile << "evolveStone " << ((pet->ateEvolveStone) ? 1 : 0 ) << endl;
    saveFile << "hp " << pet->currentHp << endl;
    saveFile << "happiness " << pet->currentHappiness << endl;
    saveFile << "food " << pet->currentFood << endl;
    saveFile << "poop " << pet->currentPoop << endl;
    saveFile.close();
}
void Game::ClearSave() {
    ofstream saveFile("Savefiles/save001.sav");
    saveFile << "";
    saveFile.close();
}
void Game::StartGameLoop() {

    StartProgram();
    LoadGame();
    
	while (window.isOpen()) {
		ReInitialize();
		GetInput();
		Update();
		Draw();
        if (quitGame) {
            SaveGame();
            window.close();
            cout << "Application Ended." << endl;
        }
        if (clearSave) {
            ClearSave();
            cout << "Game Reset." << endl;
            window.close();
            cout << "Application Ended." << endl;
        }
	}
}

void Game::ReInitialize() {
    deltaTime = clock.restart().asSeconds();
    fps = 1 / deltaTime;

    ResetKeyboard();
    ResetMouse();
    anyKeyPressed = anyMousePressed = false;
    mouseWheelDelta = 0;

    if (gameState == 1) {
        pet->Initialize();
    }
    backgrounds[currentBackground].Initialize();
    for (int i = 0; i < clouds.size(); ++i) {
        clouds[i].Initialize();
    }
    titlePanel->Initialize();

    
}


void Game::Update() {
    //cout << gameState << " ";
    for(int i = 0; i < particleSystems.size() ; ++i){
        if (particleSystems[i]->Update(deltaTime)) {
            DeleteParticle(i);
        }
    }

    if (keyPress["G"]) {
        for (int i = 0; i < particleSystems.size(); ++i) 
            particleSystems[i]->spawning_on = !particleSystems[i]->spawning_on;
    }
    if (keyPress["V"]) {
        clearSave = true;
    }
    if (keyPress["Z"]) {
        muteSfx = !muteSfx;
        doodle->muteSFX(muteSfx);
    }
    if (keyPress["X"]) {
        muteBgm = !muteBgm;
        doodle->muteBGM(muteBgm);
    }

    if (gameState == 0 || gameState == -1) {
        titlePanel->speed.x = titlePanelSpeed;
        titlePanel->Update(deltaTime);

        if (titlePanel->GetPosition().x > titlePanelGap) {
            titlePanelSpeed = 0;
            titlePanel->SetPosition(titlePanelGap, 160);
        }

        if (titlePanelSpeed == 0 && gameState == 0) {
            pressAnyKeyToStartBlinkTotalTime += deltaTime;
            if (pressAnyKeyToStartBlinkTotalTime > pressAnyKeyToStartBlinkTime) {
                pressAnyKeyToStartBlinkTotalTime -= pressAnyKeyToStartBlinkTime;
                pressAnyKeyToStartIsShown = !pressAnyKeyToStartIsShown;
            }
            if (anyKeyPressed || anyMousePressed) {
                if (isFirstTimePlaying) {
                    gameState = -1;
                }
                else {
                    gameState = 1;
                }
            }
        }

        if (gameState == -1) {
            for (int i = 0; i < petEggs.size(); ++i) {
                petEggs[i]->Update(deltaTime, window, mousePress, mouseHold, mousePosition, quitGame, selectedPet, clearSave, muteBgm, muteSfx, *maindishBut, *dessertBut, *etcBut);
                if (gameState == 1) {
                    if (isFirstTimePlaying) {
                        isFirstTimePlaying = false;
                        LoadGame();
                    }
                }
            }

        }
    }
    else if (gameState == 1 || gameState == 2) {
        
        pet->happinessChangeRate += poops.size()/10;
        pet->Update(deltaTime, keyPress, keyHold, keyRelease, mousePress, mouseRelease, mouseHold, mousePosition, mouseWheelDelta);
        if (pet->CanPoop()) {
            if (pet->type == "DICKO") {
                poops.push_back(pet->CreatePoop());
                poops[poops.size() - 1]->SetPosition(poops[poops.size() - 1]->GetPosition().x + 50, poops[poops.size() - 1]->GetPosition().y);
                poops.push_back(pet->CreatePoop());
                poops[poops.size() - 1]->SetPosition(poops[poops.size() - 1]->GetPosition().x - 50, poops[poops.size() - 1]->GetPosition().y);

            }
            poops.push_back(pet->CreatePoop());
        }

        for (int i = 0; i < poops.size(); ++i) {
            if (CheckPoopIntegrity(i)) {
                sfx[0].play();
                particleSystems.push_back(new ParticleSystem(1, 0, -90, 1, 7, Vector2f(40, 40), poops[i]->GetPosition(), "Assets/Textures/Coin.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 1, poops[i]->GetPosition().y+30, 1, true, true));
                DeletePoop(i);
            }
        }

        for (int i = 0; i < poops.size(); ++i) {
            if (poops[i]->Update(deltaTime, window, mousePress, mousePosition)) {
                particleSystems.push_back(new ParticleSystem(20, 180, 0, 0.5, 4, Vector2f(10, 10), poops[i]->GetPosition(), "Assets/Textures/ps_poop_clickedon.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 1, poops[i]->floorLine+25, 1, true, true));
            }
        }

        shopBut->Update(deltaTime, window, mousePress, mouseHold, mousePosition, quitGame, selectedPet, clearSave, muteBgm, muteSfx, *maindishBut, *dessertBut, *etcBut);
        miniBut->Update(deltaTime, window, mousePress, mouseHold, mousePosition, quitGame, selectedPet, clearSave, muteBgm, muteSfx, *maindishBut, *dessertBut, *etcBut);
        exitBut->Update(deltaTime, window, mousePress, mouseHold, mousePosition, quitGame, selectedPet, clearSave, muteBgm, muteSfx, *maindishBut, *dessertBut, *etcBut);
        resetBut->Update(deltaTime, window, mousePress, mouseHold, mousePosition, quitGame, selectedPet, clearSave, muteBgm, muteSfx, *maindishBut, *dessertBut, *etcBut);
        mutebgmBut->Update(deltaTime, window, mousePress, mouseHold, mousePosition, quitGame, selectedPet, clearSave, muteBgm, muteSfx, *maindishBut, *dessertBut, *etcBut);
        mutesfxBut->Update(deltaTime, window, mousePress, mouseHold, mousePosition, quitGame, selectedPet, clearSave, muteBgm, muteSfx, *maindishBut, *dessertBut, *etcBut);
        evolveButton->Update(deltaTime, window, mousePress, mouseHold, mousePosition, quitGame, selectedPet, clearSave, muteBgm, muteSfx, *maindishBut, *dessertBut, *etcBut);
        leftBut->Update(deltaTime, window, mousePress, mouseHold, mousePosition, quitGame, selectedPet, clearSave, muteBgm, muteSfx, *maindishBut, *dessertBut, *etcBut);
        rightBut->Update(deltaTime, window, mousePress, mouseHold, mousePosition, quitGame, selectedPet, clearSave, muteBgm, muteSfx, *maindishBut, *dessertBut, *etcBut);
        maindishBut->Update(deltaTime, window, mousePress, mouseHold, mousePosition, quitGame, selectedPet, clearSave, muteBgm, muteSfx, *maindishBut, *dessertBut, *etcBut);
        dessertBut->Update(deltaTime, window, mousePress, mouseHold, mousePosition, quitGame, selectedPet, clearSave, muteBgm, muteSfx, *maindishBut, *dessertBut, *etcBut);
        etcBut->Update(deltaTime, window, mousePress, mouseHold, mousePosition, quitGame, selectedPet, clearSave, muteBgm, muteSfx, *maindishBut, *dessertBut, *etcBut);
        doodle->Update(deltaTime, keyPress, pet->currentLevel, *pet);

        shop->Update(deltaTime, mouseWheelDelta);

        UpdateUI();
        ReInitializeUI();
    }


    mouseCursor->SetPosition(mousePosition.x, mousePosition.y);
    mouseCursor->Update(deltaTime);
        
    backgrounds[currentBackground].Update(deltaTime);
    for (int i = 0; i < clouds.size(); ++i) {
        clouds[i].speed = Vector2f(cloudSpeed, 0);

        clouds[i].Update(deltaTime);
        if (clouds[i].GetPosition().x > windowWidth) {

            clouds[i].SetPosition(-((clouds.size() - 2) * cloudGap), clouds[i].GetPosition().y);
        }
    }

    string fpsString = to_string(fps);
    fpsString.erase(fpsString.end() - 4, fpsString.end());
    fpsText.setString(fpsString);
    
    if (!muteBgm) {
        if (bgm.getStatus() == SoundSource::Status::Paused || bgm.getStatus() == SoundSource::Status::Stopped) {
            currentBgm++;
            if (currentBgm >= bgmVariables.size()) {
                currentBgm = 0;
            }
            PlaySound(bgm, currentBgm, "BGM");
        }

    }
    else {
        bgm.pause();

    }
    
    if (!muteSfx) {

    }
    else {
        for (int i = 0; i < sfx.size(); ++i) {
            if (sfx[i].getStatus() == SoundSource::Status::Playing) {
                cout << "pause game sfx " << i << endl;
                sfx[i].pause();
            }
        }
        for (int i = 0; i < pet->sfx.size(); ++i) {
            if (pet->sfx[i].getStatus() == SoundSource::Status::Playing) {
                cout << "pause pet sfx " << i << endl;
                pet->sfx[i].pause();
            }
        }
        for (int i = 0; i < poops.size(); ++i) {
            for (int j = 0; j < poops[i]->sfx.size(); ++j) {
                if (poops[i]->sfx[j].getStatus() == SoundSource::Status::Playing) {
                    cout << "pause poop " << i  << " sfx "  << " " << j << endl;
                    poops[i]->sfx[j].pause();
                }
                
            }
        }

    }

    //cout << deltaTime << " " << fps << endl;
}


void Game::Draw() {
    window.clear(Color::Black);
    //Draw things here vvvv


    backgrounds[currentBackground].Draw(window);
 

    for (int i = 0; i < clouds.size(); ++i) {
        clouds[i].Draw(window);
    }

    if (gameState == -1 && isFirstTimePlaying) {
        for (int i = 0; i < petEggs.size(); ++i) {
            petEggs[i]->Draw(window);
        }
    }
    

    if (gameState == 0) {
        titlePanel->Draw(window);
        if (pressAnyKeyToStartIsShown) {
            window.draw(pressAnyKeyToStartText);
        }
    }
    if (gameState == 1 || gameState == 2 && !isFirstTimePlaying) {

        
        shop->Draw(window);
        DrawUI(window);
        vector<GameObject*> drawQueue;
        drawQueue.push_back(pet);
        for (int i = 0; i < poops.size(); ++i) {
            drawQueue.push_back(poops[i]);
        }
        sort(drawQueue.begin(), drawQueue.end(), CompareDrawLayer);
        for (int i = 0; i < drawQueue.size(); ++i) {
            if (drawQueue[i] == pet) {
                pet->Draw(window);
            }
            else {
                drawQueue[i]->Draw(window);
            }

        }

        shopBut->Draw(window);
        miniBut->Draw(window);
        exitBut->Draw(window);
        resetBut->Draw(window);
        mutebgmBut->Draw(window);
        mutesfxBut->Draw(window);
        evolveButton->Draw(window);
        if (shop->isOpen == true) {
            maindishBut->Draw(window);
            dessertBut->Draw(window);
            etcBut->Draw(window);
        }
        doodle->Draw(window);
        if (doodle->gstate == 3) {
            leftBut->Draw(window);
            rightBut->Draw(window);
        }
        

        

    }
    for (int i = 0; i < particleSystems.size(); ++i) {
        if (particleSystems[i]) {
            particleSystems[i]->Draw(window);
        }
    }

    if (pet->isAlive == false) {
        yourPetDied->Draw(window);
    }


    window.draw(fpsText);


    mouseCursor->Draw(window);

    //Display
    window.display();
}


void Game::ReInitializeUI() {
    ui_topPanel_front->Initialize();
    ui_topPanel_back->Initialize();
    ui_hpBar->Initialize();
    ui_foodBar->Initialize();
    ui_poopBar->Initialize();
    ui_expBar->Initialize();
    ui_happinessBar->Initialize();

}
void Game::UpdateUI() {

    ui_hpBar->SetDimensions((float)pet->currentHp / pet->hpMax[pet->currentLevel] * ui_barWidth, ui_barHeight);
    ui_foodBar->SetDimensions((float)pet->currentFood / pet->foodMax[pet->currentLevel] * ui_barWidth, ui_barHeight);
    ui_poopBar->SetDimensions((float)pet->currentPoop / pet->poopMax[pet->currentLevel] * ui_barWidth, ui_barHeight);

    ui_expBar->SetDimensions((float)pet->currentExp / pet->expPerEvolve[pet->currentLevel] * ui_expBarWidth, ui_expBarHeight);

    ui_happinessBarHeight = (float)pet->currentHappiness / pet->happinessMax[pet->currentLevel] * ui_happinessBarMaxHeight;
    ui_happinessBar->SetPosition(410, ui_happinessBarFloorLevel - ui_happinessBarHeight);
    ui_happinessBar->SetDimensions(ui_happinessBarWidth, ui_happinessBarHeight);

    string tempStr = "";

    tempStr = to_string(pet->currentHp);   tempStr.erase(tempStr.begin() + tempStr.find('.') + 2, tempStr.end());
    ui_currentHp.setString(tempStr);
    tempStr = to_string(pet->currentFood);   tempStr.erase(tempStr.begin() + tempStr.find('.') + 2, tempStr.end());
    ui_currentFood.setString(tempStr);
    tempStr = to_string(pet->currentPoop);   tempStr.erase(tempStr.begin() + tempStr.find('.') + 2, tempStr.end());
    ui_currentPoop.setString(tempStr);
    tempStr = to_string(pet->currentExp);   tempStr.erase(tempStr.begin() + tempStr.find('.'), tempStr.end());
    ui_currentExp.setString(tempStr);
    ui_currentLevel.setString(to_string(pet->currentLevel + 1));
     
    
    tempStr = to_string(pet->hpMax[pet->currentLevel]);  tempStr.erase(tempStr.begin() + tempStr.find('.'), tempStr.end());
    ui_hpMax.setString("/" + tempStr);
    tempStr = to_string(pet->foodMax[pet->currentLevel]);  tempStr.erase(tempStr.begin() + tempStr.find('.'), tempStr.end());
    ui_foodMax.setString("/" + tempStr);
    tempStr = to_string(pet->poopMax[pet->currentLevel]);  tempStr.erase(tempStr.begin() + tempStr.find('.'), tempStr.end());
    ui_poopMax.setString("/" + tempStr);
    tempStr = to_string(pet->expPerEvolve[pet->currentLevel]);  tempStr.erase(tempStr.begin() + tempStr.find('.'), tempStr.end());
    ui_expMax.setString("/" + tempStr);


    SetTextAlignment(ui_currentHp, 335+15, 1);
    SetTextAlignment(ui_currentFood, 335+15, 1);
    SetTextAlignment(ui_currentPoop, 335+15, 1);
    SetTextAlignment(ui_currentExp, 520+20, 1);
    SetTextAlignment(ui_currentLevel, 635, 2);



    float emotionPoint = pet->happinessPoint;
    if (pet->isAlive == false) {
        emotionFrame = 4;
    }
    else if (emotionPoint > 210/310.0f) {
        emotionFrame = 0;
    }
    else if (emotionPoint > 120 / 310.0f) {
        emotionFrame = 1;
    }
    else if (emotionPoint > 50 / 310.0f) {
        emotionFrame = 2;
    }
    else if (emotionPoint >= 0) {
        emotionFrame = 3;
    }
    
    ui_emotionIcon->SetFrame(emotionFrame, 0);
    ui_emotionIcon->Update(deltaTime);

    ui_money.setString(to_string(pet->money));
    SetTextAlignment(ui_money, 640, 2);
}
void Game::DrawUI(RenderWindow& window) {

    ui_topPanel_back->Draw(window);

    ui_hpBar->Draw(window);
    ui_foodBar->Draw(window);
    ui_poopBar->Draw(window);
    ui_expBar->Draw(window);
    ui_happinessBar->Draw(window);
    ui_emotionIcon->Draw(window);

    //window.draw(ui_hpText);
    window.draw(ui_hpMax);
    window.draw(ui_currentHp);
    //window.draw(ui_foodText);
    window.draw(ui_foodMax);
    window.draw(ui_currentFood);
    //window.draw(ui_poopText);
    window.draw(ui_poopMax);
    window.draw(ui_currentPoop);
    //window.draw(ui_expText);
    window.draw(ui_expMax);
    window.draw(ui_currentExp);

    window.draw(ui_money);
    window.draw(ui_levelText);
    window.draw(ui_currentLevel);

    ui_topPanel_front->Draw(window);


}


bool Game::CheckPoopIntegrity(int index) {
    return poops[index]->nClickToDestroy <= 0;
}
void Game::DeletePoop(int index) {
    pet->money += poops[index]->price;
    delete poops[index];
    poops.erase(poops.begin() + index);
}

void Game::DeleteParticle(int index)
{
    delete particleSystems[index];
    particleSystems.erase(particleSystems.begin() + index);
}

void Game::GetInput() {
    while (window.pollEvent(evnt)) {
        switch (evnt.type) {
        case Event::Closed:
            window.close();
            break;
        case Event::Resized:
            cout << evnt.size.width << " " << evnt.size.height << endl;
            break;
        case Event::TextEntered:
            if (evnt.text.unicode < 128) {
                //cout << (char)evnt.text.unicode;
            }
            break;
        case Event::KeyPressed:
            anyKeyPressed = true;
            CheckKeyPressRelease(&keyPress, &evnt);
            break;
        case Event::KeyReleased:
            CheckKeyPressRelease(&keyRelease, &evnt);
            break;
        case Event::MouseButtonPressed:
            anyMousePressed = true;
            CheckMousePressRelease(&mousePress, &evnt);
            //CheckMousePressRelease(&mousePress);
            break;
        case Event::MouseButtonReleased:
            CheckMousePressRelease(&mouseRelease, &evnt);
            //CheckMousePressRelease(&mouseRelease);
            break;
        case Event::MouseWheelScrolled:
            mouseWheelDelta = evnt.mouseWheelScroll.delta;
            break;
        case Event::MouseMoved:
            mousePosition = Mouse::getPosition(window);
            break;
        }
    }
    //mouseWheelDelta = evnt.mouseWheelScroll.delta;

    pet->Clamp(&mousePosition.x, windowWidth, 0);
    pet->Clamp(&mousePosition.y, windowHeight, 0);

    CheckMousePressRelease(&mouseHold);
    CheckKeyPressRelease(&keyHold);
    /*CheckKeyPressRelease(&keyRelease);
    CheckMousePressRelease(&mousePress);
    CheckMousePressRelease(&mouseRelease);*/
}
void Game::CheckKeyPressRelease(unordered_map<string, bool> *keyFlag) {
    int state = true;
    if (Keyboard::isKeyPressed(Keyboard::W)) {
       (*keyFlag)["W"] = state;
    }
    if (Keyboard::isKeyPressed(Keyboard::A)) {
        (*keyFlag)["A"] = state;
    }
    if (Keyboard::isKeyPressed(Keyboard::S)) {
        (*keyFlag)["S"] = state;
    }
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        (*keyFlag)["D"] = state;
    }
    if (Keyboard::isKeyPressed(Keyboard::Space)) {
        (*keyFlag)["SPACE"] = state;
    }
    if (Keyboard::isKeyPressed(Keyboard::LShift)) {
        (*keyFlag)["LSHIFT"] = state;
    }
    if (Keyboard::isKeyPressed(Keyboard::LControl)) {
        (*keyFlag)["LCTRL"] = state;
    }
    if (Keyboard::isKeyPressed(Keyboard::Enter)) {
        (*keyFlag)["ENTER"] = state;
    }
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        (*keyFlag)["ESC"] = state;
    }
    if (Keyboard::isKeyPressed(Keyboard::Tab)) {
        (*keyFlag)["TAB"] = state;
    }
    if (Keyboard::isKeyPressed(Keyboard::Q)) {
        (*keyFlag)["Q"] = state;
    }
    if (Keyboard::isKeyPressed(Keyboard::E)) {
        (*keyFlag)["E"] = state;
    }
    if (Keyboard::isKeyPressed(Keyboard::R)) {
        (*keyFlag)["R"] = state;
    }
    if (Keyboard::isKeyPressed(Keyboard::T)) {
        (*keyFlag)["T"] = state;
    }
    if (Keyboard::isKeyPressed(Keyboard::F)) {
        (*keyFlag)["F"] = state;
    }
    if (Keyboard::isKeyPressed(Keyboard::G)) {
        (*keyFlag)["G"] = state;
    }
    if (Keyboard::isKeyPressed(Keyboard::Z)) {
        (*keyFlag)["Z"] = state;
    }
    if (Keyboard::isKeyPressed(Keyboard::X)) {
        (*keyFlag)["X"] = state;
    }
    if (Keyboard::isKeyPressed(Keyboard::C)) {
        (*keyFlag)["C"] = state;
    }
    if (Keyboard::isKeyPressed(Keyboard::V)) {
        (*keyFlag)["V"] = state;
    }
    if (Keyboard::isKeyPressed(Keyboard::B)) {
        (*keyFlag)["B"] = state;
    }
}

void Game::CheckKeyPressRelease(unordered_map<string, bool>* keyFlag, Event* evnt) {
    int state = true;
    if (evnt->key.code == (Keyboard::W)) {
        (*keyFlag)["W"] = state;
    }
    if (evnt->key.code == (Keyboard::A)) {
        (*keyFlag)["A"] = state;
    }
    if (evnt->key.code == (Keyboard::S)) {
        (*keyFlag)["S"] = state;
    }
    if (evnt->key.code == (Keyboard::D)) {
        (*keyFlag)["D"] = state;
    }
    if (evnt->key.code == (Keyboard::Space)) {
        (*keyFlag)["SPACE"] = state;
    }
    if (evnt->key.code == (Keyboard::LShift)) {
        (*keyFlag)["LSHIFT"] = state;
    }
    if (evnt->key.code == (Keyboard::LControl)) {
        (*keyFlag)["LCTRL"] = state;
    }
    if (evnt->key.code == (Keyboard::Enter)) {
        (*keyFlag)["ENTER"] = state;
    }
    if (evnt->key.code == (Keyboard::Escape)) {
        (*keyFlag)["ESC"] = state;
    }
    if (evnt->key.code == (Keyboard::Tab)) {
        (*keyFlag)["TAB"] = state;
    }
    if (evnt->key.code == (Keyboard::Q)) {
        (*keyFlag)["Q"] = state;
    }
    if (evnt->key.code == (Keyboard::E)) {
        (*keyFlag)["E"] = state;
    }
    if (evnt->key.code == (Keyboard::R)) {
        (*keyFlag)["R"] = state;
    }
    if (evnt->key.code == (Keyboard::T)) {
        (*keyFlag)["T"] = state;
    }
    if (evnt->key.code == (Keyboard::F)) {
        (*keyFlag)["F"] = state;
    }
    if (evnt->key.code == (Keyboard::G)) {
        (*keyFlag)["G"] = state;
    }
    if (evnt->key.code == (Keyboard::Z)) {
        (*keyFlag)["Z"] = state;
    }
    if (evnt->key.code == (Keyboard::X)) {
        (*keyFlag)["X"] = state;
    }
    if (evnt->key.code == (Keyboard::C)) {
        (*keyFlag)["C"] = state;
    }
    if (evnt->key.code == (Keyboard::V)) {
        (*keyFlag)["V"] = state;
    }
    if (evnt->key.code == (Keyboard::B)) {
        (*keyFlag)["B"] = state;
    }
}

void Game::CheckMousePressRelease(unordered_map<string, bool>* mouseFlag) {
    int state = true;
    if (Mouse::isButtonPressed(Mouse::Left)) {
        (*mouseFlag)["M1"] = state;
    }
    if (Mouse::isButtonPressed(Mouse::Right)) {
        (*mouseFlag)["M2"] = state;
    }
    if (Mouse::isButtonPressed(Mouse::Middle)) {
        (*mouseFlag)["M3"] = state;
    }
}

void Game::CheckMousePressRelease(unordered_map<string, bool>* mouseFlag, Event* evnt) {
    int state = true;
    if (evnt->mouseButton.button == Mouse::Left) {
        (*mouseFlag)["M1"] = state;
    }
    if (evnt->mouseButton.button == Mouse::Right) {
        (*mouseFlag)["M2"] = state;
    }
    if (evnt->mouseButton.button == Mouse::Middle) {
        (*mouseFlag)["M3"] = state;
    }
}

void Game::ResetKeyboard() {
    unordered_map<string, bool> keyboardResetState = {
        {"W",0},{"A",0},{"S",0},{"D",0},
        {"SPACE",0},{"LSHIFT",0},{"LCTRL",0},
        {"ENTER",0},{"ESC",0},{"TAB",0},
        {"Q",0},{"E",0},{"R",0},{"T",0},
        {"F",0},{"G",0},
        {"Z",0},{"X",0},{"C",0},{"V",0},
    };
    keyPress = keyRelease = keyHold = keyboardResetState;
}

void Game::ResetMouse() {
    unordered_map<string, bool> mouseResetState = {
        {"M1",0},{"M2",0},{"M3",0},
    };
    mousePress = mouseRelease = mouseHold = mouseResetState;
}

void Game::SetTextUI(Text& text, string str, Font& font, Color color, int size, Vector2f position) {
    text.setString(str);
    text.setFont(font);
    text.setFillColor(color);
    text.setCharacterSize(size);
    text.setPosition(position);
}

void Game::SetTextAlignment(Text& text, float anchorPositionX, int alignment) {
    if (alignment == 0) {
        text.setPosition(anchorPositionX, text.getPosition().y);
    }
    else if (alignment == 1) {
        text.setPosition(anchorPositionX - text.getLocalBounds().width, text.getPosition().y);
    }
    else if (alignment == 2) {
        text.setPosition(anchorPositionX - text.getLocalBounds().width/2, text.getPosition().y);
    }
    

}

void Game::PlaySound(Sound& soundPlayer, int soundBufferIndex, string type) {
    cout << "Playing " << type << " : " << soundBufferIndex << endl;
    soundPlayer.setVolume(bgmVariables[soundBufferIndex].volume);
    soundPlayer.setBuffer(bgmSoundBuffers[soundBufferIndex]);
    soundPlayer.play();
}