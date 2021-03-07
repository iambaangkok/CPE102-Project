#include "Game.h"


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

void Game::LoadGame() {
    Font font1;
    if (!font1.loadFromFile("Assets/Fonts/Minecraftia.ttf"))
        throw("COULD NOT LOAD FONT! ");
    fonts.push_back(font1);


    static ParticleSystem bobo = ParticleSystem(3, 30, 60, 10, 10, Vector2f(100, 100), Vector2f(windowWidth / 2, windowHeight / 2), "Assets/Textures/DefaultTexture.png",
        Vector2u(5, 3), Vector2i(1, 0), Vector2i(2, 0), 0.3f);
    test1 = &bobo;

    //Opensavefile, Calculate expgain foodloss etc.

    /// Pet
    float playerSize = 160.0f;
    static Pet p = Pet(Vector2f((float)(windowWidth / 2), (float)(windowHeight / 2)), Vector2f(playerSize, playerSize), true,
        "Assets/Textures/pet_01_x2.png", Vector2u(5, 3), Vector2i(1, 0), Vector2i(2, 0), 0.3f,
        "Fluffball", "Dragon", 3, vector<int>{100, 150, 200}, vector<int>{ 100, 200, 300 }, vector<int>{ 100, 120, 140 }, vector<int>{ 100, 120, 140 }, vector<int>{ 80, 90, 100 },
        5,5,20,5,5,0.2f);
    pet = &p;

    static GameObject pShadow = GameObject(Vector2f((float)(windowWidth / 2), (float)(windowHeight / 2)), Vector2f(140, 60), true,
        "Assets/Textures/shadow_01.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 10);
    pet->shadow = &pShadow;

    float grassFieldTopBorder = 560;
    float grassFieldHeight = 730 - 560;
    float grassFieldThickness = 1000;
    //1 = right, 2 = left, 3 = bottom, 4 = top
    static GameObject pBorder1 = GameObject(Vector2f(windowWidth+grassFieldThickness/2,grassFieldTopBorder+grassFieldHeight / 2), Vector2f(grassFieldThickness, grassFieldHeight), true,
        "Assets/Textures/DefaultTexture.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 10);
    static GameObject pBorder2 = GameObject(Vector2f(0-grassFieldThickness+grassFieldThickness / 2, grassFieldTopBorder + grassFieldHeight / 2), Vector2f(grassFieldThickness, grassFieldHeight), true,
        "Assets/Textures/DefaultTexture.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 10);
    static GameObject pBorder3 = GameObject(Vector2f(windowWidth/2, grassFieldTopBorder-grassFieldThickness/2), Vector2f(windowWidth, grassFieldThickness), true,
        "Assets/Textures/DefaultTexture.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 10);
    static GameObject pBorder4 = GameObject(Vector2f(windowWidth/2, grassFieldTopBorder+grassFieldHeight+grassFieldThickness/2), Vector2f(windowWidth, grassFieldThickness), true,
        "Assets/Textures/DefaultTexture.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 10);
    
    pet->shadowBorder.push_back(pBorder1);
    pet->shadowBorder.push_back(pBorder2);
    pet->shadowBorder.push_back(pBorder3);
    pet->shadowBorder.push_back(pBorder4);


    /// User Interface
    static GameObject mCS = GameObject(Vector2f(0, 0), Vector2f(64, 64), false, "Assets/Textures/mouseCursor.png", Vector2u(4, 1), Vector2i(0, 0), Vector2i(0, 0), 1);
    mouseCursor = &mCS;

    static GameObject ui_tp_f = GameObject(Vector2f(0, 0), Vector2f(windowWidth, 200), false, "Assets/Textures/panel_top_x3_front.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 10);
    ui_topPanel_front = &ui_tp_f;

    static GameObject ui_tp_b = GameObject(Vector2f(0, 0), Vector2f(windowWidth, 200), false, "Assets/Textures/panel_top_x3_back.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 10);
    ui_topPanel_back = &ui_tp_b;


    static GameObject ui_hpb = GameObject(Vector2f(90, 40), Vector2f((float)p.currentHp / p.hpMax[p.currentLevel] * ui_barWidth, ui_barHeight), false,
        "Assets/Textures/panel_top_x3_hpBar.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 10);
    ui_hpBar = &ui_hpb;
    static GameObject ui_fb = GameObject(Vector2f(90, 80), Vector2f((float)p.currentFood / p.foodMax[p.currentLevel] * ui_barWidth, ui_barHeight), false,
        "Assets/Textures/panel_top_x3_foodBar.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 10);
    ui_foodBar = &ui_fb;
    static GameObject ui_pb = GameObject(Vector2f(90, 120), Vector2f((float)p.currentPoop / p.poopMax[p.currentLevel] * ui_barWidth, ui_barHeight), false,
        "Assets/Textures/panel_top_x3_poopBar.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 10);
    ui_poopBar = &ui_pb;

    static GameObject ui_expb = GameObject(Vector2f(90, 160), Vector2f((float)p.currentExp / p.expPerEvolve[p.currentLevel] * ui_expBarWidth, ui_expBarHeight), false,
        "Assets/Textures/panel_top_x3_expBar.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 10);
    ui_expBar = &ui_expb;

    ui_happinessBarHeight = (float)p.currentHappiness / p.happinessMax[p.currentLevel] * ui_happinessBarMaxHeight;
    static GameObject ui_hab = GameObject(Vector2f(400, ui_happinessBarFloorLevel - ui_happinessBarHeight), Vector2f(ui_happinessBarWidth, ui_happinessBarHeight), false, Color(255,255,255));
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
    SetTextUI(ui_hpMax, "/" + to_string(pet->hpMax[pet->currentLevel]), fonts[0], col_BLACK1, fontSize, Vector2f(335 + gapXPlus - 5 , 60));
    SetTextUI(ui_currentHp, to_string(pet->currentHp), fonts[0], col_BLACK1, fontSize - 2, Vector2f(335 - gapXMinus, 50));

    //SetTextUI(ui_foodText, "FOOD", fonts[0], col_BLACK1, 20, Vector2f(40, 80));
    SetTextUI(ui_foodMax, "/" + to_string(pet->foodMax[pet->currentLevel]), fonts[0], col_BLACK1, fontSize, Vector2f(330 + gapXPlus, 100));
    SetTextUI(ui_currentFood, to_string(pet->currentFood), fonts[0], col_BLACK1, fontSize - 2, Vector2f(335 - gapXMinus, 90));

    //SetTextUI(ui_poopText, "POO", fonts[0], col_BLACK1, 20, Vector2f(40, 120));
    SetTextUI(ui_poopMax, "/" + to_string(pet->poopMax[pet->currentLevel]), fonts[0], col_BLACK1, fontSize, Vector2f(330 + gapXPlus, 140));
    SetTextUI(ui_currentPoop, to_string(pet->currentPoop), fonts[0], col_BLACK1, fontSize - 2, Vector2f(335 - gapXMinus, 130));

    //SetTextUI(ui_expText, "EXP", fonts[0], col_BLACK1, 20, Vector2f(40, 160));
    SetTextUI(ui_expMax, "/" + to_string(pet->expPerEvolve[pet->currentLevel]), fonts[0], col_BLACK1, fontSize, Vector2f(520 + gapXPlus-5, 180));
    SetTextUI(ui_currentExp, to_string(pet->currentExp), fonts[0], col_BLACK1, fontSize - 2, Vector2f(520 - gapXMinus+5, 170));

    SetTextUI(ui_money, to_string(pet->currentExp), fonts[0], col_BLACK1, 20, Vector2f(630, 65));
    SetTextUI(ui_levelText, "LEVEL", fonts[0], col_BLACK1, 20, Vector2f(600, 120));
    SetTextUI(ui_currentLevel, to_string(pet->currentLevel+1), fonts[0], col_BLACK1, 20, Vector2f(635, 140));



    /// Shop
    static Shop s = Shop();
    shop = &s;      

    static Button sB = Button(Vector2f(210, 890), Vector2f(130, 140), false,
        "Assets/Textures/button_yellow_01.png", Vector2u(5, 1), Vector2i(0, 0), Vector2i(0, 0),1
        ,"sB", 0 , "SHOP",gameState,*shop, *pet);
    sB.animation.freezeFrame = true;
    shopBut = &sB;

    /// Minigames
    static Button mnB = Button(Vector2f(380, 890), Vector2f(130, 140), false,
        "Assets/Textures/button_blue_01.png", Vector2u(5, 1), Vector2i(0, 0), Vector2i(0, 0), 1
        , "mnB", 0, "MINIGAME", gameState,*shop, *pet);
    mnB.animation.freezeFrame = true;
    miniBut = &mnB;

    static Doodle d = Doodle(gameState);
    doodle = &d;
    doodle->Initialize();

    /// BuyItems
    for (int i = 0; i < 18; ++i) {
        static Button bB = Button(Vector2f(380, 890), Vector2f(130, 140), false,
            "Assets/Textures/button_blue_01.png", Vector2u(5, 1), Vector2i(0, 0), Vector2i(0, 0), 1
            , "bB", 0, "BUYITEM", gameState, *shop,*pet, i+1);
        bB.animation.freezeFrame = true;
        buyBut.push_back(bB);
    }

    /// Miscellaneous
    static GameObject bg = GameObject(Vector2f(0, 0), Vector2f(windowWidth, windowHeight), false, "Assets/Textures/BGMain.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 1);
    backgrounds.push_back(bg);

    static GameObject cloud1 = GameObject(Vector2f(0, -10), Vector2f(120, 60), false, "Assets/Textures/clouds_01.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 1);
    static GameObject cloud2 = GameObject(Vector2f(0, +10), Vector2f(200, 80), false, "Assets/Textures/clouds_02.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 1);
    clouds.push_back(cloud1);
    clouds.push_back(cloud2);
    clouds.push_back(cloud1);
    clouds.push_back(cloud2);
    for (int i = 0; i < clouds.size(); ++i) {
        clouds[i].SetPosition(-(i * cloudGap + 120), cloudPosY + clouds[i].GetPosition().y);
    }

    static GameObject ti = GameObject(Vector2f(-titlePanelGap-titlePanelWidth-titlePanelGap, 160), Vector2f(titlePanelWidth, titlePanelHeight), false, "Assets/Textures/title_bordered.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 1);
    titlePanel = &ti;

    pressAnyKeyToStartText.setString("Press Any Key to Start");
    pressAnyKeyToStartText.setFont(fonts[0]);
    pressAnyKeyToStartText.setFillColor(Color::White);
    pressAnyKeyToStartText.setCharacterSize(25);
    pressAnyKeyToStartText.setPosition(windowWidth/2 - 180, titlePanelHeight + 160 + 40);
    pressAnyKeyToStartText.setStyle(Text::Bold);

    fpsText.setString(to_string(fps));
    fpsText.setFont(fonts[0]);
    fpsText.setFillColor(Color::Black);
    fpsText.setCharacterSize(16);
    fpsText.setPosition(windowWidth - 40, 10);

}


void Game::StartGameLoop() {
	while (window.isOpen()) {
		ReInitialize();
		GetInput();
		Update();
		Draw();
	}
}

void Game::ReInitialize() {
    deltaTime = clock.restart().asSeconds();
    fps = 1 / deltaTime;

    ResetKeyboard();
    ResetMouse();
    anyKeyPressed = anyMousePressed = false;
    mouseWheelDelta = 0;


    pet->Initialize();
    backgrounds[currentBackground].Initialize();
    for (int i = 0; i < clouds.size(); ++i) {
        clouds[i].Initialize();
    }
    titlePanel->Initialize();

    
}


void Game::Update() {
   
    mouseCursor->SetPosition(mousePosition.x,mousePosition.y);
    mouseCursor->Update(deltaTime);

    test1->Update(deltaTime);
    
    pet->Update(deltaTime, keyPress,keyHold,keyRelease,mousePress,mouseRelease,mouseHold, mousePosition,mouseWheelDelta);

    backgrounds[currentBackground].Update(deltaTime);
    for(int i = 0 ; i < clouds.size(); ++i){
        clouds[i].speed = Vector2f(cloudSpeed,0);
        
        clouds[i].Update(deltaTime);
        if (clouds[i].GetPosition().x > windowWidth) {
            clouds[i].SetPosition(-((clouds.size()-2) * cloudGap), clouds[i].GetPosition().y);
        }
    }

    titlePanel->speed.x = titlePanelSpeed;
    titlePanel->Update(deltaTime);

    if (titlePanel->GetPosition().x > titlePanelGap) {
        titlePanelSpeed = 0;
        titlePanel->SetPosition(titlePanelGap, 160);
    }

    string fpsString = to_string(fps);
    fpsString.erase(fpsString.end() - 4, fpsString.end());
    fpsText.setString(fpsString);

    if (titlePanelSpeed == 0 && gameState == 0) {
        pressAnyKeyToStartBlinkTotalTime += deltaTime;
        if (pressAnyKeyToStartBlinkTotalTime > pressAnyKeyToStartBlinkTime) {
            pressAnyKeyToStartBlinkTotalTime -= pressAnyKeyToStartBlinkTime;
            pressAnyKeyToStartIsShown = !pressAnyKeyToStartIsShown;
        }
        if (anyKeyPressed || anyMousePressed) {
            gameState = 1;
        }
    }

    shopBut->Update(deltaTime, window, mousePress, mousePosition);
    miniBut->Update(deltaTime, window, mousePress, mousePosition);
    doodle->Update(deltaTime , keyPress);
    
    shop->Update( deltaTime, mouseWheelDelta);

    ReInitializeUI();

    UpdateUI();

    cout << deltaTime << " " << fps << endl;
}




void Game::Draw() {
    window.clear(Color::Black);
    //Draw things here vvvv


    backgrounds[currentBackground].Draw(window);
 
    DrawUI(window);

   shop->Draw(window);

    for (int i = 0; i < clouds.size(); ++i) {
        clouds[i].Draw(window);
    }

    if (gameState == 0) {
        titlePanel->Draw(window);
        if (pressAnyKeyToStartIsShown) {
            window.draw(pressAnyKeyToStartText);
        }
    }
    if (gameState == 1) {
        pet->Draw(window);
    }
    
    shopBut->Draw(window);
    miniBut->Draw(window);
    test1->Draw(window);

    window.draw(fpsText);

    doodle->Draw(window);

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

    ui_currentHp.setString(to_string(pet->currentHp));
    ui_currentFood.setString(to_string(pet->currentFood));
    ui_currentPoop.setString(to_string(pet->currentPoop));
    ui_currentExp.setString(to_string(pet->currentExp));
    ui_currentLevel.setString(to_string(pet->currentLevel));

    SetTextAlignment(ui_currentHp, 335+15, 1);
    SetTextAlignment(ui_currentFood, 335+15, 1);
    SetTextAlignment(ui_currentPoop, 335+15, 1);
    SetTextAlignment(ui_currentExp, 520+20, 1);
    SetTextAlignment(ui_currentLevel, 635, 2);



    float emotionPoint = (float)pet->currentHappiness / pet->happinessMax[pet->currentLevel];
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
    SetTextAlignment(ui_money, 630, 2);
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
