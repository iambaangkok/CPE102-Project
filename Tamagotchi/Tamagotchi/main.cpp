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
#include "Doodle.h"
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

    srand(time(0));
    /*
    LoadGameData();

    Game tamagotchi(window);
    tamagotchi.LoadGame();
    tamagotchi.StartGameLoop();
    
    SaveGameData();
    */

    Doodle doodle;
    doodle.Initialize();
    Clock clock;

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        Event evnt;

        while (window.pollEvent(evnt)) {
            if (evnt.type == evnt.Closed) {
                window.close();
            }
        }

        doodle.Update(deltaTime);
        doodle.Draw(window);
        window.display();
    }
    return 0;
}
