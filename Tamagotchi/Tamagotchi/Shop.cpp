#include "Shop.h"
#include "Item.h"
Shop::Shop(int& gstate, Pet& pet, Doodle& doodle) {  
  
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
    AddItem("Hotdog","ShopItem8.png",gstate, this, pet, doodle);
    AddItem("Noodle69","ShopItem9.png",gstate, this, pet, doodle);
    AddItem("Chicken","ShopItem14.png", gstate, this, pet, doodle);
    AddItem("Waxwowald","ShopItem13.png", gstate, this, pet, doodle);
    
    AddItem("Cocola", "ShopItem12.png", gstate, this, pet, doodle);
    AddItem("Bubble tea", "ShopItem2.png", gstate, this, pet, doodle);
    AddItem("Bubble tea", "ShopItem3.png", gstate, this, pet, doodle);
    AddItem("Bubble tea","ShopItem4.png", gstate, this, pet, doodle);
    AddItem("Mochi","ShopItem10.png", gstate, this, pet, doodle);
    //AddItem("Dango","ShopItem11.png");
   

    AddItem("Evo I","ShopItem1.png", gstate, this, pet, doodle);
    AddItem("Evo II","ShopItem1.png", gstate, this, pet, doodle);
    AddItem("Evo III","ShopItem1.png", gstate, this, pet, doodle);

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
  

    for (int i = 0; i < buy1.size(); i++)
    {
        buy1[i]->SetPosition(corePosition + 330, (i * 180) + 440);
    }
    for (int i = 0; i < buy2.size(); i++)
    {
        buy2[i]->SetPosition(corePosition + 330, (i * 180) + 440);

    }
    for (int i = 0; i < buy3.size(); i++)
    {
        buy3[i]->SetPosition(corePosition + 330, (i * 180) + 440);
    }
    

    static GameObject bgrshop = GameObject(Vector2f(corePosition, 200), Vector2f(400, 70), false, "Assets/Textures/button_manu1.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 1);
    bgbar = &bgrshop;//Ba


    static GameObject scroll = GameObject(Vector2f(positionscrollX , 200), Vector2f(10, heightscrollbar), false, "Assets/Textures/panel_blue_72x20.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 1);
    scrollbar = &scroll; //Scroll
    
    static GameObject upper = GameObject(Vector2f(0,0), Vector2f(720,200), false, "Assets/Textures/Upper.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 1);
    up = &upper;
    static GameObject lower = GameObject(Vector2f(0,820), Vector2f(720, 220), false, "Assets/Textures/Lower.png", Vector2u(1, 1), Vector2i(0, 0), Vector2i(0, 0), 1);
    low = &lower;

    
}
Shop::~Shop() {
}

void Shop::AddItem(string itemName, string texturePath, int& gstate, Shop* shop, Pet& pet, Doodle& doodle) {
    Vector2f itemPictureSize(400, 180);
    Vector2u imageCount(1, 1);
    Vector2i start(0, 0);
    Vector2i finish(0, 0);

    int fontSize = 14;
   
    Item* newItem = new Item(Vector2f(0, 0), itemPictureSize, false, "Assets/Textures/Shop/" + texturePath, imageCount, start, finish, 1, itemName);
    newItem->itemId;
    Button* newbutton = new Button(Vector2f (340,520), Vector2f (70,25), false, "Assets/Textures/button_buy.png", Vector2u (5,1), Vector2i (0,0), Vector2i (0,0),  1,
        "bB", 0, "BUYITEM",gstate, *this, pet, doodle);
    newbutton->animation.freezeFrame = true;
    newbutton->id = newItem->itemId;
    newbutton->enable = true;

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

        newbutton->text = newItem->type;
        buy1.push_back(newbutton);
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

        newbutton->text = newItem->type;
        buy2.push_back(newbutton);
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

        newbutton->text = newItem->type;
        buy3.push_back(newbutton);
    }
}
void Shop::Draw(RenderWindow &window) {
    if (isOpen) {
        scrollbar->Draw(window);
        cout << status << endl;
        if (status == "food") {
  
            for (int i = 0; i < itemfood.size(); i++)
            {
                itemfood[i]->Draw(window);
                for (int j = 0; j < food[i].size(); ++j) {
                    window.draw(food[i][j]);
                }
                
            }
            for (int i = 0; i < buy1.size(); ++i) {
                buy1[i]->Draw(window);
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
            for (int i = 0; i < buy2.size(); ++i) {
                buy2[i]->Draw(window);
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
            for (int i = 0; i < buy3.size(); ++i) {
                buy3[i]->Draw(window);
            }
        }
        
        bgbar->Draw(window);
        up->Draw(window);
        low->Draw(window);
    }
    else {
    }
}

void Shop::Update(float deltaTime, int mouseWheelDelta,
    RenderWindow& window, unordered_map<string, bool>& mousePress, unordered_map<string, bool>& mouseHold, Vector2i& mousePosition,
    bool& quitGame, int& selectedPet, bool& clearSave, bool& muteBgm, bool& muteSfx, Button& foodButton, Button& candyButton, Button& etcc) {
    if (isOpen) {
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
            for (int i = 0; i < buy1.size(); ++i) {
                buy1[i]->Update(deltaTime, window, mousePress, mouseHold, mousePosition, quitGame, selectedPet, clearSave, muteBgm, muteSfx, foodButton, candyButton, etcc);
                buy1[i]->SetPosition(corePosition + 330, (i * 180) + 440 - timey+180);
            }
        } 
        if (status=="candy") {
           
            for (int i = 0; i < itemcandy.size(); i++)
            {
                itemcandy[i]->SetPosition(corePosition, ((i * 180) + corePositiony+200) - timey);
                for (int j = 0; j < candy[i].size(); ++j)
                {
                    candy[i][j].setPosition(corePosition + textofset[j].x, ((i * 180) + corePositiony - itemTextOffset) - timey + textofset[j].y);

                }
            }//candy
            for (int i = 0; i < buy2.size(); ++i) {
                buy2[i]->Update(deltaTime, window, mousePress, mouseHold, mousePosition, quitGame, selectedPet, clearSave, muteBgm, muteSfx, foodButton, candyButton, etcc);
                buy2[i]->SetPosition(corePosition + 330, (i * 180) + 440 - timey+180);
            }
        }
        if (status=="etc") {
           
            for (int i = 0; i < itemetc.size(); i++)
            {
                itemetc[i]->SetPosition(corePosition, ((i * 180) + corePositiony+200)- timey);
                for (int j = 0; j < etc[i].size(); ++j)
                {   
                    etc[i][j].setPosition(corePosition + textofset[j].x, ((i * 180) + corePositiony - itemTextOffset) - timey + textofset[j].y);

                }
            }
            for (int i = 0; i < buy3.size(); ++i) {
                buy3[i]->Update(deltaTime, window, mousePress, mouseHold, mousePosition, quitGame, selectedPet, clearSave, muteBgm, muteSfx, foodButton, candyButton, etcc);
                buy3[i]->SetPosition(corePosition + 330, (i * 180) + 440 - timey+180);
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