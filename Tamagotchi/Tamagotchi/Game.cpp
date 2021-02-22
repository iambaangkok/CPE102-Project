#include "Game.h"


Game::Game(RenderWindow& mainWindow) : window(mainWindow){

	window.setFramerateLimit(frameRateLimit);  
	deltaTime = 0;
	clock.restart();
}


Game::~Game() {

}

void Game::LoadGame() {

    //Opensavefile, Calculate expgain foodloss etc.

    float playerSize = 100.0f;
    static Pet p = Pet(Vector2f((float)(windowWidth / 2), (float)(windowHeight / 2)), Vector2f(playerSize, playerSize), true,
        "Assets/Textures/testTextureLARGE.png", Vector2u(16, 11), Vector2i(12, 10), Vector2i(14, 10), 0.3f,
        "Fluffball", "Dragon", 3, vector<int>{20, 30, 40}, vector<int>{ 100, 200, 300 }, vector<int>{ 30, 30, 30 }, vector<int>{ 20, 25, 30 }, vector<int>{ 10, 10, 10 });
    pet = &p;

    static Shop s = Shop();
    shop = &s;

    static Button sB = Button(Vector2f(210,890), Vector2f(130,80), false,
        "Assets/Textures/testbutton2.png", Vector2u(4,1), Vector2i(0,0), Vector2i(0,0),1
        ,"sB", 0 , "SHOPBUTTON",gameState,shop->isOpen);
    sB.animation.freezeFrame = true;
    shopBut = &sB;

    static Button mnB = Button(Vector2f(380, 890), Vector2f(130,80), false,
        "Assets/Textures/testbutton2.png", Vector2u(4, 1), Vector2i(0, 0), Vector2i(0, 0), 1
        , "mnB", 0, "MINIGAMEBUTTON", gameState, shop->isOpen);
    mnB.animation.freezeFrame = true;
    miniBut = &mnB;

    static GameObject bg = GameObject(Vector2f(0, 0), Vector2f(windowWidth, windowHeight), false, "Assets/Textures/background_01.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 1);
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

    Font font1;
    if (!font1.loadFromFile("Assets/Fonts/Minecraftia.ttf"))
        throw("COULD NOT LOAD FONT! ");
    fonts.push_back(font1);

    fpsText.setString(to_string(fps));
    fpsText.setFont(fonts[0]);
    fpsText.setFillColor(Color::Black);
    fpsText.setCharacterSize(16);
    fpsText.setPosition(windowWidth-40, 10);

    pressAnyKeyToStartText.setString("Press Any Key to Start");
    pressAnyKeyToStartText.setFont(fonts[0]);
    pressAnyKeyToStartText.setFillColor(Color::White);
    pressAnyKeyToStartText.setCharacterSize(25);
    pressAnyKeyToStartText.setPosition(windowWidth/2 - 180, titlePanelHeight + 160 + 40);
    pressAnyKeyToStartText.setStyle(Text::Bold);

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

    pet->Initialize();
    backgrounds[currentBackground].Initialize();
    for (int i = 0; i < clouds.size(); ++i) {
        clouds[i].Initialize();
    }
    titlePanel->Initialize();
}


void Game::Update() {
    

    if (keyHold["W"]) {
        pet->speed.y = -pet->maxSpeed.y;
    }
    if (keyHold["A"]) {
        pet->speed.x = -pet->maxSpeed.x;
        pet->faceRight = false;
    }
    if (keyHold["S"]) {
        pet->speed.y = +pet->maxSpeed.y;
    }
    if (keyHold["D"]) {
        pet->speed.x = +pet->maxSpeed.x;
        pet->faceRight = true;
    }
    if (mousePress["M1"]) {
        pet->SetPosition(Vector2f(mousePosition.x, mousePosition.y));
    }


    
    pet->Update(deltaTime);
    backgrounds[currentBackground].Update(deltaTime);
    for(int i = 0 ; i < clouds.size(); ++i){
        clouds[i].speed = Vector2f(cloudSpeed,0);
        //cout << clouds[i].speed.x << " ";
        
        clouds[i].Update(deltaTime);
        if (clouds[i].GetPosition().x > windowWidth) {
            clouds[i].SetPosition(-((clouds.size()-2) * cloudGap), clouds[i].GetPosition().y);
        }
        //cout << clouds[i].GetPosition().x << " " << endl ;
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

    if (titlePanelSpeed == 0) {
        pressAnyKeyToStartBlinkTotalTime += deltaTime;
        if (pressAnyKeyToStartBlinkTotalTime > pressAnyKeyToStartBlinkTime) {
            pressAnyKeyToStartBlinkTotalTime -= pressAnyKeyToStartBlinkTime;
            pressAnyKeyToStartIsShown = !pressAnyKeyToStartIsShown;
        }
        if (anyKeyPressed || anyMousePressed) {
            gameState = 1;
        }
    }

    shopBut->Update(deltaTime, window, mousePress);
    miniBut->Update(deltaTime, window, mousePress);

    
}

void Game::Draw() {
    window.clear(Color::Black);//Clear


    //Draw other things
    backgrounds[currentBackground].Draw(window);
    
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

    window.draw(fpsText);

    window.display();//Display
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
            CheckKeyPressRelease(&keyPress);
            break;
        case Event::KeyReleased:
            CheckKeyPressRelease(&keyRelease);
            break;
        case Event::MouseButtonPressed:
            anyMousePressed = true;
            //CheckMousePressRelease(&mousePress);
            break;
        case Event::MouseButtonReleased:
            //CheckMousePressRelease(&mouseRelease);
            break;
        case Event::MouseWheelMoved:
            mouseWheelDelta = evnt.mouseWheel.delta;
            break;
        case Event::MouseMoved:
            mousePosition = Mouse::getPosition(window);
            break;
        }
    }
    CheckMousePressRelease(&mousePress);
    CheckMousePressRelease(&mouseRelease);
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
    mousePress = mouseRelease = mouseResetState;
}

