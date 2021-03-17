#include "Shop.h"
#include "Item.h"
Shop::Shop() {
  
    Font font;
    if (!font.loadFromFile("Assets/Fonts/arial.ttf"))
        throw(" CLOUD NOT LOAD FONT! ");
    //for (int i = 0; i < items.size(); ++i) {
        //Text description;
        //description.setFont(font);
        //description.setFillColor(Color(219, 138, 6, 125));
        //description.setCharacterSize(25);
        //description.setString(items[i]->description);
        //description.setPosition(100, 1040 / 2);
        //descriptions.push_back(description);
    //}
    AddItem("hotdog","ShopItem8.png");
    AddItem("noodle69","ShopItem9.png");
    AddItem("chicken drumstick","ShopItem14.png");
    AddItem("waxwowald","ShopItem13.png");
    
    AddItem("cocola", "ShopItem12.png"); 
    AddItem("bubble tea1", "ShopItem2.png");
    AddItem("bubble tea2", "ShopItem3.png");
    AddItem("bubble tea3","ShopItem4.png");
    AddItem("mochi","ShopItem10.png");
    AddItem("dango","ShopItem11.png");
   
    AddItem("evo1","ShopItem1.png");
    AddItem("evo2","ShopItem1.png");
    AddItem("evo3","ShopItem1.png");




    
    for (int i = 0; i < itemfood.size(); i++)    
    {
        itemfood[i]->SetPosition(corePosition, (i * 180) + 270);
    }//food
    for (int i = 0; i < itemcandy.size(); i++)
    {
        itemcandy[i]->SetPosition(corePosition, (i * 180) + 270);
    }//candy
    for (int i = 0; i < itemetc.size(); i++)
    {
        itemetc[i]->SetPosition(corePosition, (i * 180) + 270);
    }//etc
    //static GameObject bgr = GameObject(Vector2f(0, 0), Vector2f(windowWidth, windowHeight), false,"Assets/Textures/button_manu1.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 1);
    // bg = &bgr; 

    static GameObject bgrshop = GameObject(Vector2f(corePosition, 200), Vector2f(400, 70), false, "Assets/Textures/button_manu1.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 1);
    bgbar = &bgrshop;//Ba


    static GameObject scroll = GameObject(Vector2f(positionscrollX , 200), Vector2f(10, heightscrollbar), false, "Assets/Textures/panel_blue_72x20.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 1);
    scrollbar = &scroll; //Scroll
    



   //static GameObject item = GameObject(Vector2f(corePosition, 270), Vector2f(400, 180), false, "Assets/Textures/Shop/item/ShopItem99.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 1);
   // picitem = &item; // shop in item.

   // static Item ii = Item(Vector2f(corePosition, 270+200), Vector2f(400, 180), false, "Assets/Textures/Shop/item/ShopItem99.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 1, "noodle69");
   // test1 = &ii;
    static GameObject upper = GameObject(Vector2f(0,0), Vector2f(720,200), false, "Assets/Textures/Upper.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 1);
    up = &upper;
    static GameObject lower = GameObject(Vector2f(0,820), Vector2f(720, 220), false, "Assets/Textures/Lower.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 1);
    low = &lower;

}
Shop::~Shop() {
}

void Shop::AddItem(string itemName, string texturePath) {
    Vector2f itemPictureSize(400, 180);
    Vector2u imageCount(1, 1);
    Vector2i start(0, 0);
    Vector2i finish(0, 0);

    //static GameObject item = GameObject(Vector2f(corePosition, 270), Vector2f(400, 180), false, "Assets/Textures/Shop/item/ShopItem99.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 1);
    Item* newItem = new Item(Vector2f(0, 0), itemPictureSize, false, "Assets/Textures/Shop/" + texturePath, imageCount, start, finish, 1, itemName);
    if (newItem->type == "food")
    {
        itemfood.push_back(newItem);
    }
    if (newItem->type == "candy")
    {
        itemcandy.push_back(newItem);
    }
    if (newItem->type == "etc")
    {
        itemetc.push_back(newItem);
    }

}
void Shop::Draw(RenderWindow &window) {
    if (isOpen) {
        //bg->Draw(window);
        up->Draw(window);
        bgbar->Draw(window);
        scrollbar->Draw(window);
        //picitem->Draw(window);
        if (buttons[0]==0) {
            for (int i = 0; i < itemfood.size(); i++)
            {
                itemfood[i]->Draw(window);
            }
        }
        if (buttons[1]==1){
            for (int i = 0; i < itemcandy.size(); i++)
            {
                itemcandy[i]->Draw(window);
            }
        }
        if (buttons[2]==2) {
            for (int i = 0; i < itemetc.size(); i++)
            {
                itemetc[i]->Draw(window);
            }
        }
        low->Draw(window);
        //test1->Draw(window);
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
       
       /* for (int i = 1; i < itemfood.size(); i++)
        {
            itemfood[i]->SetPosition(corePosition, (i * 180) + 270);
        }//food
        for (int i = 1; i < itemcandy.size(); i++)
        {
            itemcandy[i]->SetPosition(corePosition, (i * 180) + 270);
        }//candy
        for (int i = 1; i < itemetc.size(); i++)
        {
            itemetc[i]->SetPosition(corePosition, (i * 180) + 270);
        }*/
        
        if () {
            for (int i = 0; i < itemfood.size(); i++)
            {
                itemfood[i]->Update(deltaTime);
            }
            for (int i = 1; i < itemfood.size(); i++)
            {
                itemfood[i]->SetPosition(corePosition, (i * 180) + 270 - scrollbar->GetPosition().y + 0 - mouseWheelDelta * deltaTime * speedscroll);
            }//food


        } // �Ѿവ 
        if () {
            for (int i = 0; i < itemcandy.size(); i++)
            {
                itemcandy[i]->Update(deltaTime);
            }
            for (int i = 1; i < itemcandy.size(); i++)
            {
                itemcandy[i]->SetPosition(corePosition, (i * 180) + 270 - scrollbar->GetPosition().y + 0 - mouseWheelDelta * deltaTime * speedscroll);
            }//candy
        }
        if () {
            for (int i = 0; i < itemetc.size(); i++)
            {
                itemetc[i]->Update(deltaTime);
            }
            for (int i = 1; i < itemetc.size(); i++)
            {
                itemetc[i]->SetPosition(corePosition, (i * 180) + 270 - scrollbar->GetPosition().y + 0 - mouseWheelDelta * deltaTime * speedscroll);
            }
        }
        //test1->Update(deltaTime);
    }
}


