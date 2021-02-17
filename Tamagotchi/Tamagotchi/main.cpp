#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <vector>
#include "Game.h"
#include "Animation.h"
#include "GameObject.h"
#include "GravityObject.h"
#include "Pet.h"
#include "PlatformObject.h"
#include "Button.h"
#include "Item.h"
#include "Shop.h"
using namespace sf;

using std::cout;
using std::endl;


int windowWidth = 720;
int windowHeight = 1040;
string title = "Tamagotchi";
RenderWindow window(VideoMode(windowWidth, windowHeight), title, Style::Close | Style::Titlebar | Style::Resize);

void LoadGameData() {
    //Read save files and set data
}

void SaveGameData() {
    //Read variables then save as save file
    //Delete dynamic memories
}


int main() {
    
    LoadGameData();

    Game tamagotchi(window);
    tamagotchi.LoadGame();
    tamagotchi.StartGameLoop();
    
    SaveGameData();

    
    
    //RenderWindow window(VideoMode(windowWidth, windowHeight), "Tamagotchi", Style::Close | Style::Titlebar | Style::Resize);
    //int frameRateLimit = 60;
    //window.setFramerateLimit(60);

    //Vector2f maxPlayerSpeed = Vector2f(5, 5);
    //Vector2f playerSpeed = Vector2f(0, 0);
    ////float playerSpeed = 5.0f;
    //float playerWidth = 80.0f;
    //float playerHeight = 80.0f;
    //
    ////GameObject player(Vector2f(0, 0), Vector2f(playerWidth, playerHeight), true, "Assets/Textures/testTextureLARGE.png", Vector2u(16,11), Vector2i(13, 10));
    ////GameObject defaultGameObject;
    ////GameObject player(Vector2f(100, 100), Vector2f(playerWidth, playerHeight), true, "Assets/Textures/testTextureLARGE.png");
    //GravityObject Alpha(Vector2f(80.0f, 80.0f), Vector2f(playerWidth , playerHeight), 500.0f, 350.0f);
    //PlatformObject Platform(Vector2f(68.0f, 14.0f), Vector2i(windowWidth, windowHeight), 10);
    //Platform.Initialize();
    ////GameObject platform(Vector2f(100.0f, 800.0f), Vector2f(1000.0f, 50.0f), true);

    ////Pet player(Vector2f((float)(windowWidth / 2), (float)(windowHeight / 2)), Vector2f(playerWidth, playerHeight), true, "Assets/Textures/testTextureLARGE.png", Vector2u(16, 11), Vector2i(12, 10), Vector2i(14, 10), 0.3f,
    ////    "Fluffball", "Dragon", 3, vector<int>{20,30,40}, vector<int>{ 100,200,300 }, vector<int>{ 30,30,30 }, vector<int>{ 20,25,30 }, vector<int>{ 10,10,10 });

    //float deltaTime = 0.0f;
    //Clock clock;
    //Font font;
    //if (!font.loadFromFile("Assets/Fonts/arial.ttf"))// ��ʢͧfont
    //    throw(" CLOUD NOT LOAD FONT! ");
    //Text text;
    //text.setFont(font);
    //text.setFillColor(Color(219,138,6,125));
    //text.setCharacterSize(25);
    //text.setString("BoBo is the best of game year."); // ��ͤ���
    //text.setPosition(10.f, windowHeight/ 2);
    //text.move(0.1f, 0.f);
    //float cnt = 0;
    //bool _switch = false;
    //vector<Color> colorVector;
    //colorVector.push_back(Color(255,255, 255, 255));
    //colorVector.push_back(Color(20, 20, 20, 255));
    //colorVector.push_back(Color::Green);
    //colorVector.push_back(Color::Cyan);
    //Button testButton(Vector2f(20, 20), Vector2f(545, 566), true, "Assets/Textures/testbutton.jpg", Vector2u(1, 1), Vector2i(1, 1), Vector2i(1, 1), 100, colorVector, "Button", 0, "Dont know");

    //while (window.isOpen()) { //GAMELOOP
    //    ///INITIALIZE
    //    deltaTime = clock.restart().asSeconds();
    //    Event evnt;
    //    
    //    //player.Initialize();
    //    


    //    ///  GET INPUT
    //    tamagotchi.ReInitialize();
    //    tamagotchi.GetInput();
    //    while (window.pollEvent(evnt)) {

    //        switch (evnt.type) {
    //        case Event::Closed:
    //            window.close();
    //            break;
    //        case Event::Resized:
    //            cout << evnt.size.width << " " << evnt.size.height << endl;
    //            break;
    //        case Event::TextEntered:
    //            if (evnt.text.unicode < 128) {
    //                cout << (char)evnt.text.unicode;
    //            }

    //        }

    //    }
    //    
    //    //if (Keyboard::isKeyPressed(Keyboard::W)) {
    //    //    //playerSpeed.y = -maxPlayerSpeed.y;
    //    //    player.speed.y = -player.maxSpeed.y;
    //    //}
    //    //if (Keyboard::isKeyPressed(Keyboard::A)) {
    //    //    //playerSpeed.x = -maxPlayerSpeed.x;
    //    //    player.speed.x = -player.maxSpeed.x;
    //    //    player.faceRight = false;
    //    //}
    //    //if (Keyboard::isKeyPressed(Keyboard::S)) {
    //    //    //playerSpeed.y = +maxPlayerSpeed.y;
    //    //    player.speed.y = +player.maxSpeed.y;
    //    //}
    //    //if (Keyboard::isKeyPressed(Keyboard::D)) {
    //    //    //playerSpeed.x = +maxPlayerSpeed.x;
    //    //    player.speed.x = +player.maxSpeed.x;
    //    //    player.faceRight = true;
    //    //}

    //    //if (Mouse::isButtonPressed(Mouse::Left)) {
    //    //    Vector2i mousePos = Mouse::getPosition(window);
    //    //    player.rectangleShape.setPosition((float)mousePos.x, static_cast<float>(mousePos.y));
    //    //}

    //    ///// UPDATE
    //    //player.Update(deltaTime);
    //    ////player.Update(player.animation.startFrame, player.animation.finishFrame, deltaTime);
    //    ////player.Move(playerSpeed.x, playerSpeed.y);
    //    ////player.Update(10,deltaTime, true);
    //    ////player.Update(deltaTime);
    //    //
    //    tamagotchi.Update();
    //    testButton.Update(deltaTime,window,tamagotchi.mousePress);
    //    Alpha.Update(deltaTime);
    //    //platform1.CheckCollision(player, 1.0f);
    //    
    //    for (unsigned int i = 0; i < Platform.platform.size(); ++i) {
    //        if (Alpha.velocity.y > 0 && Platform.platform[i].CheckCollision(Alpha, 1.0f))
    //            Alpha.OnCollision(Alpha.direction);
    //    }
    //    
    //    //if(platform1.CheckCollision(Alpha, 1.0f))
    //    //    Alpha.OnCollision(Alpha.direction);
    //    
    //    
    //    

    //    /// DRAW
    //    window.clear(Color::Black);
    //    tamagotchi.Draw();
    //    testButton.Draw(window);

    //    Platform.Draw(window);
    //    Alpha.Draw(window);
    //    //defaultGameObject.Draw(window);
    //    //player.Draw(window);
    //    
    //    
    //    
    //    //for (unsigned int i = 0; i < platform.size(); ++i) {
    //    //    platform[i].Draw(window);
    //    //}
    //    
    //    //platform1.Draw(window);

    //    window.draw(text);

    //    window.display();
    //    //cout << deltaTime << " " << animation.switchTime << endl;

    //    }

    return 0;
}
