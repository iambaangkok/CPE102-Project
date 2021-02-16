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





}


Shop::~Shop() {

}