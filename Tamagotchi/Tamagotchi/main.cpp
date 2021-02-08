#include <SFML\Graphics.hpp>
#include <iostream>
#include "Animation.h"

using namespace sf;
//using sf::Event;
//using sf::RenderWindow;
//using sf::VideoMode;

using std::cout;
using std::endl;

int main() {

    float windowWidth = 512;
    float windowHeight = 512;
    RenderWindow window(VideoMode(windowWidth, windowHeight), "Tamagotchi", Style::Close | Style::Titlebar | Style::Resize);
    int frameRateLimit = 60;
    window.setFramerateLimit(60);

    float playerSpeed = 0.1f;
    float playerWidth = 100;
    float playerHeight = 100;
    
    RectangleShape player(Vector2f(playerWidth, playerHeight));
    
    player.setOrigin(playerWidth / 2, playerHeight / 2);
    
    //player.setFillColor(Color::Green);

    Texture playerTexture;
    playerTexture.loadFromFile("testTextureLarge.png");
    player.setTexture(&playerTexture);

    Animation animation(&playerTexture, Vector2u(16, 11), 0.3f); 

    float deltaTime = 0.0f;
    Clock clock;

    Vector2u textureSize = playerTexture.getSize();
    textureSize.x /= 16;
    textureSize.y /= 11;

    //player.setTextureRect(IntRect(textureSize.x * 13, textureSize.y * 10, textureSize.x, textureSize.y));



    while (window.isOpen()) {

        deltaTime = clock.restart().asSeconds();
        Event evnt;
        while (window.pollEvent(evnt)) {

            switch (evnt.type) {
            case Event::Closed:
                window.close();
                break;
            case Event::Resized:
                cout << evnt.size.width << " " << evnt.size.height << endl;
                break;
            case Event::TextEntered:
                if (evnt.text.unicode < 128);
                cout << (char)evnt.text.unicode;    

            }

        }

        if(Keyboard::isKeyPressed(Keyboard::W)) {
            player.move(0, -playerSpeed);
        }
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            player.move(-playerSpeed, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            player.move(0, playerSpeed);
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            player.move(playerSpeed, 0);
        }

        if (Mouse::isButtonPressed(Mouse::Left)) {
            Vector2i mousePos = Mouse::getPosition(window);
            player.setPosition((float)mousePos.x, static_cast<float>(mousePos.y));
        }


        animation.Update(9, deltaTime, false);
        player.setTextureRect(animation.uvRect);

        window.clear(Color::White);
        window.draw(player);
        window.display();
        //cout << deltaTime << " " << animation.switchTime << endl;

    }

    return 0;
}

