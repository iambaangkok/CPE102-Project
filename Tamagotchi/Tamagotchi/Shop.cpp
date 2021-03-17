#include "Shop.h"
#include "Item.h"
Shop::Shop() {  
  
    if (!font.loadFromFile("Assets/Fonts/Minecraftia.ttf"))
        throw(" CLOUD NOT LOAD FONT! ");
    for (int i = 0; i < items.size(); ++i) {
        Text description;
        description.setFont(font);
        description.setFillColor(Color(219, 138, 6, 125));
        description.setCharacterSize(25);
        description.setString(items[i]->description);
        description.setPosition(100, 1040 / 2);
        descriptions.push_back(description);
    }
    AddItem("Hotdog","ShopItem8.png");
    AddItem("Noodle69","ShopItem9.png");
    AddItem("Chicken","ShopItem14.png");
    AddItem("Waxwowald","ShopItem13.png");
    
    AddItem("Cocola", "ShopItem12.png"); 
    AddItem("Bubble tea I", "ShopItem2.png");
    AddItem("Bubble tea II", "ShopItem3.png");
    AddItem("Bubble tea III","ShopItem4.png");
    AddItem("Mochi","ShopItem10.png");
    AddItem("Dango","ShopItem11.png");
   

    AddItem("Evo I","ShopItem1.png");
    AddItem("Evo II","ShopItem1.png");
    AddItem("Evo III","ShopItem1.png");

    textofset.push_back(Vector2f(230, 320));
    textofset.push_back(Vector2f(225, 385));
    textofset.push_back(Vector2f(290, 385));
    textofset.push_back(Vector2f(350, 385));
    textofset.push_back(Vector2f(280, 435));
  
    
    for (int i = 0; i < itemfood.size(); i++)    
    {
        itemfood[i]->SetPosition(corePosition, (i * 180) + 470);
    }//food
    for (int i = 0; i < itemcandy.size(); i++)
    {
        itemcandy[i]->SetPosition(corePosition, (i * 180) + 470);
    }//candy
    for (int i = 0; i < itemetc.size(); i++)
    {
        itemetc[i]->SetPosition(corePosition, (i * 180) + 470);
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

    int fontSize = 14;
    //static GameObject item = GameObject(Vector2f(corePosition, 270), Vector2f(400, 180), false, "Assets/Textures/Shop/item/ShopItem99.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 1);
    Item* newItem = new Item(Vector2f(0, 0), itemPictureSize, false, "Assets/Textures/Shop/" + texturePath, imageCount, start, finish, 1, itemName);
    if (newItem->type == "food")
    {
        itemfood.push_back(newItem);

        vector<Text> thisItemsText;

        for(int i = 0  ; i < 5 ;++i)
            thisItemsText.push_back(Text());
        for (int i = 0; i < itemfood.size();++i) {
            SetTextShop(thisItemsText[0], newItem->name, font, col_BLACK1, 20, Vector2f(corePosition + 230, (i * 180) + 320));
            SetTextShop(thisItemsText[1], to_string(newItem->hpChange), font, col_BLACK1, fontSize, Vector2f(corePosition+ 225, (i * 180) + 385));
            SetTextShop(thisItemsText[2], to_string(newItem->foodChange), font, col_BLACK1, fontSize, Vector2f(corePosition + 290, (i * 180) + 385));
            SetTextShop(thisItemsText[3], to_string(newItem->happinessChange), font, col_BLACK1, fontSize, Vector2f(corePosition+350, (i * 180) + 385));
            SetTextShop(thisItemsText[4], to_string(newItem->price), font, col_BLACK1, fontSize, Vector2f(corePosition+280, (i * 180) + 435));
        }
        food.push_back(thisItemsText);
    }
    if (newItem->type == "candy")
    {
        itemcandy.push_back(newItem);
        vector<Text> thisItemsText;

        for (int i = 0; i < 5; ++i)
            thisItemsText.push_back(Text());

        for (int i = 0; i < itemfood.size(); ++i) {
            SetTextShop(thisItemsText[0], newItem->name, font, col_BLACK1, 20, Vector2f(corePosition + 230, (i * 180) + 320));
            SetTextShop(thisItemsText[1], to_string(newItem->hpChange), font, col_BLACK1, fontSize, Vector2f(corePosition + 225, (i * 180) + 385));
            SetTextShop(thisItemsText[2], to_string(newItem->foodChange), font, col_BLACK1, fontSize, Vector2f(corePosition + 290, (i * 180) + 385));
            SetTextShop(thisItemsText[3], to_string(newItem->happinessChange), font, col_BLACK1, fontSize, Vector2f(corePosition + 350, (i * 180) + 385));
            SetTextShop(thisItemsText[4], to_string(newItem->price), font, col_BLACK1, fontSize, Vector2f(corePosition + 280, (i * 180) + 435));
        }

        candy.push_back(thisItemsText);
    }
    if (newItem->type == "etc")
    {
        itemetc.push_back(newItem);
        vector<Text> thisItemsText;

        for (int i = 0; i < 5; ++i)
            thisItemsText.push_back(Text());

        for (int i = 0; i < itemfood.size(); ++i) {
            SetTextShop(thisItemsText[0], newItem->name, font, col_BLACK1, 20, Vector2f(corePosition + 230, (i * 180) + 320));
            SetTextShop(thisItemsText[1], to_string(newItem->hpChange), font, col_BLACK1, fontSize, Vector2f(corePosition + 225, (i * 180) + 385));
            SetTextShop(thisItemsText[2], to_string(newItem->foodChange), font, col_BLACK1, fontSize, Vector2f(corePosition + 290, (i * 180) + 385));
            SetTextShop(thisItemsText[3], to_string(newItem->happinessChange), font, col_BLACK1, fontSize, Vector2f(corePosition + 350, (i * 180) + 385));
            SetTextShop(thisItemsText[4], to_string(newItem->price), font, col_BLACK1, fontSize, Vector2f(corePosition + 280, (i * 180) + 435));
        }
        etc.push_back(thisItemsText);
    }
}
void Shop::Draw(RenderWindow &window) {
    if (isOpen) {
        //bg->Draw(window);
        scrollbar->Draw(window);
        //picitem->Draw(window);

        if (status == "food") {
            for (int i = 0; i < itemfood.size(); i++)
            {
                itemfood[i]->Draw(window);
                for (int j = 0; j < food[i].size(); ++j) {
                    window.draw(food[i][j]);
                }
            }
           
        }
        if (status == "candy"){
            for (int i = 0; i < itemcandy.size(); i++)
            {
                itemcandy[i]->Draw(window);
                for (int j = 0; j < candy[i].size(); ++j) {
                    window.draw(candy[i][j]);
                }
            }
        }
        if (status == "etc") {
            for (int i = 0; i < itemetc.size(); i++)
            {
                itemetc[i]->Draw(window);
                for (int j = 0; j < etc[i].size(); ++j) {
                    window.draw(etc[i][j]);
                }
            }
        }
        
        bgbar->Draw(window);
        up->Draw(window);
        low->Draw(window);
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

        float timey = scrollbar->GetPosition().y + 0 - mouseWheelDelta * deltaTime * speedscroll;
        float itemOffset = 200;
        float itemTextOffset = 70;
        if (status=="food") {
           
            for (int i = 0; i < itemfood.size(); i++)
            {
                itemfood[i]->SetPosition(corePosition, ((i * 180) + corePositiony + itemOffset) - timey);
                 
                for (int j = 0; j < food[i].size(); ++j) 
                {
                     food[i][j].setPosition(corePosition + textofset[j].x,((i * 180) + corePositiony - itemTextOffset) - timey + textofset[j].y);
                        
                }
            }//food
        } // 
        if (status=="candy") {
           
            for (int i = 0; i < itemcandy.size(); i++)
            {
                itemcandy[i]->SetPosition(corePosition, ((i * 180) + corePositiony+200) - timey);
            }//candy
        }
        if (status=="etc") {
           
            for (int i = 0; i < itemetc.size(); i++)
            {
                itemetc[i]->SetPosition(corePosition, ((i * 180) + corePositiony+200)- timey);
            }
        }
        //test1->Update(deltaTime);
    }
}

void Shop::SetTextShop(Text& text, string str, Font& font, Color color, int size, Vector2f position) {
    text.setString(str);
    text.setFont(font);
    text.setFillColor(color);
    text.setCharacterSize(size);
    text.setPosition(position);
}