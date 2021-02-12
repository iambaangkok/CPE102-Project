#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "Animation.h"
#include "GameObject.h"
#include "GravityObject.h"
#include "Pet.h"
using namespace sf;

using std::cout;
using std::endl;

int main() {

    int windowWidth = 720;
    int windowHeight = 1040;
    RenderWindow window(VideoMode(windowWidth, windowHeight), "Tamagotchi", Style::Close | Style::Titlebar | Style::Resize);
    int frameRateLimit = 60;
    window.setFramerateLimit(60);

    Vector2f maxPlayerSpeed = Vector2f(5, 5);
    Vector2f playerSpeed = Vector2f(0, 0);
    //float playerSpeed = 5.0f;
    float playerWidth = 100;
    float playerHeight = 100;
    
    //GameObject player(Vector2f(0, 0), Vector2f(playerWidth, playerHeight), true, "Assets/Textures/testTextureLARGE.png", Vector2u(16,11), Vector2i(13, 10));
    //GameObject defaultGameObject;
    //GameObject player(Vector2f(100, 100), Vector2f(playerWidth, playerHeight), true, "Assets/Textures/testTextureLARGE.png");
    //GravityObject Alpha(Vector2f(100, 100), Vector2f(playerWidth, playerHeight), true, 500.0f, 200.0f);
    //GameObject platform1(Vector2f(400.0f, 800.0f), Vector2f(1000.0f, 100.0f), true);
    Pet player(Vector2f((float)(windowWidth / 2), (float)(windowHeight / 2)), Vector2f(playerWidth, playerHeight), true, "Assets/Textures/testTextureLARGE.png", Vector2u(16, 11), Vector2i(12, 10), Vector2i(14, 10), 0.3f,
        "Fluffball", "Dragon", 3, vector<int>{20,30,40}, vector<int>{ 100,200,300 }, vector<int>{ 30,30,30 }, vector<int>{ 20,25,30 }, vector<int>{ 10,10,10 });

    float deltaTime = 0.0f;
    Clock clock;
    /*Font font;
    if (!font.loadFromFile("Assets/Fonts/arial.ttf"))// ��ʢͧfont
        throw(" CLOUD NOT LOAD FONT! ");
    Text text;
    text.setFont(font);
    text.setFillColor(Color::Black);
    text.setCharacterSize(25);
    text.setString("BoBo is the best of game year."); // ��ͤ���
    text.setPosition(10.f, windowHeight/ 2);
    text.move(0.1f, 0.f);*/
    while (window.isOpen()) {
        ///INITIALIZE
        deltaTime = clock.restart().asSeconds();
        Event evnt;
        
        player.Initialize();

        ///  GET INPUT
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
                    cout << (char)evnt.text.unicode;
                }

            }

        }
        
        if (Keyboard::isKeyPressed(Keyboard::W)) {
            //playerSpeed.y = -maxPlayerSpeed.y;
            player.speed.y = -player.maxSpeed.y;
        }
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            //playerSpeed.x = -maxPlayerSpeed.x;
            player.speed.x = -player.maxSpeed.x;
            player.faceRight = false;
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            //playerSpeed.y = +maxPlayerSpeed.y;
            player.speed.y = +player.maxSpeed.y;
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            //playerSpeed.x = +maxPlayerSpeed.x;
            player.speed.x = +player.maxSpeed.x;
            player.faceRight = true;
        }

        if (Mouse::isButtonPressed(Mouse::Left)) {
            Vector2i mousePos = Mouse::getPosition(window);
            player.rectangleShape.setPosition((float)mousePos.x, static_cast<float>(mousePos.y));
        }

        /// UPDATE
        player.Update(deltaTime);
        //player.Update(player.animation.startFrame, player.animation.finishFrame, deltaTime);
        //player.Move(playerSpeed.x, playerSpeed.y);
        //player.Update(10,deltaTime, true);
        //player.Update(deltaTime);
        
        //platform1.CheckCollision(player, 1.0f);
        

        //if(platform1.CheckCollision(Alpha, direction, 1.0f))
        //    Alpha.OnCollision(direction);


        //Alpha.Update(deltaTime);


        /// DRAW
        window.clear(Color::Black);

        //defaultGameObject.Draw(window);
        player.Draw(window);

        Vector2f direction;

        
        //Alpha.Draw(window);
        //platform1.Draw(window);

        //window.draw(text);

        window.display();
        //cout << deltaTime << " " << animation.switchTime << endl;

    }

    return 0;
}
