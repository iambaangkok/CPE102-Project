#include "Game.h"


Game::Game(RenderWindow& mainWindow) : window(mainWindow){

	window.setFramerateLimit(frameRateLimit);  
	deltaTime = 0;
	clock.restart();
}


Game::~Game() {

}

void Game::LoadGame() {
    float playerSize = 100.0f;

    static Pet p = Pet(Vector2f((float)(windowWidth / 2), (float)(windowHeight / 2)), Vector2f(playerSize, playerSize), true,
        "Assets/Textures/testTextureLARGE.png", Vector2u(16, 11), Vector2i(12, 10), Vector2i(14, 10), 0.3f,
        "Fluffball", "Dragon", 3, vector<int>{20, 30, 40}, vector<int>{ 100, 200, 300 }, vector<int>{ 30, 30, 30 }, vector<int>{ 20, 25, 30 }, vector<int>{ 10, 10, 10 });
    pet = &p;

    static Shop s = Shop();
    shop = &s;
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
    ResetKeyboard();
    ResetMouse();
    pet->Initialize();
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
            CheckKeyPressRelease(&keyPress);
            break;
        case Event::KeyReleased:
            CheckKeyPressRelease(&keyRelease);
            break;
        case Event::MouseButtonPressed:
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
}

void Game::Draw() {
    window.clear(Color::Black);
    //Draw other things
    pet->Draw(window);
    window.display();
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