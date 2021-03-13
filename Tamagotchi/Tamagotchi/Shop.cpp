#include "Shop.h"
Shop::Shop() {

    Vector2f itemPictureSize(200, 200);
    Vector2u imageCount(1, 1);
    Vector2i start(1, 1);
    Vector2i finish(1, 1);
    Item itemToPush(Vector2f(0, 0), itemPictureSize, true, "The fluffy cheesecake that perfectly sweet with a light and delicate texture, all wrapped in a crunchy Graham cracker and toasted pecan crust", imageCount, start, finish, 1, "cheeseCake");
    items.push_back(itemToPush);
    itemToPush = Item(Vector2f(0, 0), itemPictureSize, true, "A nice addition to a meal especially when outdoors.", imageCount, start, finish, 1, "honeyPeach");
    itemToPush = Item(Vector2f(0, 0), itemPictureSize, true, "Everyone know that milk is milk , nothing to describe about this thing.", imageCount, start, finish, 1, "milk");
    itemToPush = Item(Vector2f(0, 0), itemPictureSize, true, "The super ultra mega ultimate noodle that the world ever have.", imageCount, start, finish, 1, "noodle69");
    itemToPush = Item(Vector2f(0, 0), itemPictureSize, true, "A sweetened frozen food that every fat boy in the world love, contain a ton of callories", imageCount, start, finish, 1, "icecream");
    itemToPush = Item(Vector2f(0, 0), itemPictureSize, true, "Light, soft and cottony cake", imageCount, start, finish, 1, "honeyRoll");
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

    //static GameObject bgr = GameObject(Vector2f(0, 0), Vector2f(windowWidth, windowHeight), false,"Assets/Textures/button_manu1.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 1);
   // bg = &bgr; 

    static GameObject bgrshop = GameObject(Vector2f(corePosition, 270-70), Vector2f(400, 70), false, "Assets/Textures/button_manu1.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 1);
    bgs = &bgrshop;//Ba

    static GameObject scroll = GameObject(Vector2f(positionscrollX , 200), Vector2f(10, heightscrollbar), false, "Assets/Textures/panel_blue_72x20.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 1);
    scrollbar = &scroll; //Scroll
    
    static GameObject item = GameObject(Vector2f(corePosition, 270), Vector2f(400, 180), false, "Assets/Textures/Shop/item/ShopItem99.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 1);
    picitem = &item; // shop in item.

}
Shop::~Shop() {
}


void Shop::Draw(RenderWindow &window) {
    if (isOpen) {
       // bg->Draw(window);
        bgs->Draw(window);
        scrollbar->Draw(window);
        picitem->Draw(window);
    }
    else {
    }
}

void Shop::Update(float deltaTime, int mouseWheelDelta) {
    if (isOpen) {
        cout << mouseWheelDelta;
        if (mouseWheelDelta != 0){
            scrollbar->SetPosition(positionscrollX,scrollbar->GetPosition().y+0-mouseWheelDelta*deltaTime*speedscroll);
        }
        if (scrollbar->GetPosition().y < topscroll) {
            scrollbar->SetPosition(Vector2f(positionscrollX, topscroll));
        }
        if (scrollbar->GetPosition().y+heightscrollbar > lowscroll) {
            scrollbar->SetPosition(Vector2f(positionscrollX, lowscroll-heightscrollbar));
        }
    }
}


