#include "Shop.h"
Shop::Shop() {

    Vector2f itemPictureSize(200, 200);
    Vector2u imageCount(1, 1);
    Vector2i start(1, 1);
    Vector2i finish(1, 1);
    Item itemToPush(Vector2f(0, 0), itemPictureSize, true, "", imageCount, start, finish, 1, "cheeseCake");
    items.push_back(itemToPush);
    itemToPush = Item(Vector2f(0, 0), itemPictureSize, true, "", imageCount, start, finish, 1, "honeyPeach");
    itemToPush = Item(Vector2f(0, 0), itemPictureSize, true, "", imageCount, start, finish, 1, "milk");
    itemToPush = Item(Vector2f(0, 0), itemPictureSize, true, "", imageCount, start, finish, 1, "noodle69");
    itemToPush = Item(Vector2f(0, 0), itemPictureSize, true, "", imageCount, start, finish, 1, "icecream");
    itemToPush = Item(Vector2f(0, 0), itemPictureSize, true, "", imageCount, start, finish, 1, "honeyRoll");
    Font font;
    if (!font.loadFromFile("Assets/Fonts/arial.ttf"))
        throw(" CLOUD NOT LOAD FONT! ");
    for (int i = 0; i < items.size(); ++i) {
        Text description;
        description.setFont(font);
        description.setFillColor(Color(219, 138, 6, 125));
        description.setCharacterSize(25);
        description.setString(items[i].description);
        description.setPosition(100, 1040 / 2);
        descriptions.push_back(description);
    }

    static GameObject bgr = GameObject(Vector2f(0, 0), Vector2f(windowWidth, windowHeight), false,"Assets/Textures/DefaultTexture.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 1);
    bg = &bgr;

    static GameObject scroll = GameObject(Vector2f(500, 0), Vector2f(200, 550), false, "Assets/Textures/panel_blue_72x20.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 1);
    scrollbar = &scroll;

}


Shop::~Shop() {

}


void Shop::Draw(RenderWindow &window) {
    if (isOpen) {
        bg->Draw(window);
        scrollbar->Draw(window);
    }
    else {

    }
}

void Shop::Update(float deltaTime, int mouseWheelDelta) {
    if (isOpen) {
        cout << mouseWheelDelta;
        if (mouseWheelDelta != 0){
            scrollbar->SetPosition(500,scrollbar->GetPosition().y+0-mouseWheelDelta*deltaTime*speedscroll);
        }
        if (scrollbar->GetPosition().y < topscroll) {
     
            scrollbar->SetPosition(Vector2f(500, topscroll));
        }

        if (scrollbar->GetPosition().y > lowscroll) {
            scrollbar->SetPosition(Vector2f(500, lowscroll));
        }

    }

   
  

  
}
