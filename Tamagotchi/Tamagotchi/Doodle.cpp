#include "Doodle.h"


Doodle::Doodle(int& maingame_state, int hs , Pet &pet , int eq )
{
	
	this->maingame_state = &maingame_state;
	this->highscore = hs;
	this->equipnow = eq;

	Platform = new PlatformObject(Vector2f(100.0f, 20.0f), Vector2i(windowWidth, windowHeight), 8, "Assets/Textures/platform2.png");
	Alpha = new GravityObject(Vector2f(360.0f, 575.0f), Vector2f(100.0f, 100.0f), 400.0f, pet.filepath );
	Power = new PowerUp("Assets/Textures/PowerUp.png", Vector2f(19.0f * 2, 34.0f * 2));
	CoinP = new PowerUp("Assets/Textures/Coin.png" , Vector2f(34.0f * 2, 34.0f * 2));
	land = new GameObject(Vector2f(360, 800), Vector2f(720, 480), true, "Assets/Textures/background_land.png");
	landing = new ParticleSystem(20, 90, 270, 0.25, 7, Vector2f(10, 10), Vector2f(windowWidth / 2, windowHeight / 2), "Assets/Textures/Yellow.png",
		Vector2u(5, 3), Vector2i(1, 0), Vector2i(2, 0), 0.25f, windowHeight, 1, true, true);
	landing->gravity = 200.0f;

	InitBGMenu();
	InitBG();
	InitSprite();
	InitText();
	InitSound(10, 30);
}

Doodle::~Doodle()
{
}

void Doodle::Reset(Pet &pet)
{
	this->curlevel = pet.currentLevel;
	Alpha->player.SetTexture(pet.filepath);
	Alpha->player.animation.SetFrame(Vector2i(0, curlevel));
	Alpha->player.rectangleShape.setTextureRect(Alpha->player.animation.uvRect);
	Alpha->dy = -1700.0f;
	Alpha->player.SetPosition(Vector2f(360.0f, 575.0f));
	Alpha->playerX = 360.0f;
	Alpha->playerY = 575.0f;

	Platform->Reset();

	Power->state = 0;
	CoinP->state = 0;

	land_posy = 800.0f;
	land->SetPosition(Vector2f(360, land_posy));

	Logo1.setPosition(Vector2f(-250.0f, 120.0f));
	Logo2.setPosition(Vector2f(970.0f, 255.0f));

	InitBG();

	score = 0;
	scoreText.setString("Score: " + std::to_string(score));
	SetTextCenter(scoreText);
	scoreText.setPosition(Vector2f(140.0f, 60.0f));

	Money = 0;
	MoneyPickup = 0;
	money.setString("Money: " + std::to_string(0));
	SetTextCenter(money);
	money.setPosition(Vector2f(140.0f, 120.0f));

	highscoreText.setString("Highscore: " + std::to_string(highscore));
	SetTextCenter(highscoreText);
	highscoreText.setPosition(Vector2f(-200.0f, 860.0f));
	
	difficulty = 0;

	YOUDIED.setPosition(Vector2f(360, 400));
	YOUDIED.setColor(Color::Color(255, 255, 255, 0));
	FadeCnt = 0;

}

void Doodle::Update(float deltaTime , unordered_map<string, bool>&key , int curlevel , Pet &pet)
{
	//cout << " YY-> " << *maingame_state << " " << gstate<< endl;
	if (*maingame_state == 2 && pass) {
		Reset(pet);
		gstate = 0;
		pass = false;
	}
	else if (gstate == 0) // Start Screen
	{
		if (Logo1.getPosition().x < 360.0f)
			Logo1.move(Vector2f(600.0f * deltaTime, 0.0f));
		if (Logo2.getPosition().x > 360.0f)
			Logo2.move(Vector2f(-600.0f * deltaTime, 0.0f));

		/*if (key["SPACE"])
		{
			music.play();
			sound.play();
			gstate = 1;
		}*/

		/*if (key["B"])
		{
			sound.play();
			gstate = 3;
		}*/
	}
	else if (gstate == 1) // Playing
	{
		scoreText.setString("Score: " + std::to_string(score / score_rate));
		money.setString("Money: " + std::to_string(Money + MoneyPickup));

		if (Alpha->playerY == Alpha->Height && Alpha->dy < -162.0f)
		{
			score += 1;
			int MoneyNow = score / score_rate / money_rate;
			if (MoneyNow > Money) {
				Money = MoneyNow;
				coin.play();
			}
			
			difficulty = score / score_rate / difficulty_rate;
			if (difficulty > Platform->NO_OF_PLATFORM - 1)
				difficulty = Platform->NO_OF_PLATFORM - 1;
			
			if ((score / score_rate + 10) % power_range == 0 && Power->state == 0)
				Power->state = 1;
			if ((score / score_rate + 8) % coin_range == 0 && CoinP->state == 0)
				CoinP->state = 1;
		}

		Alpha->dy += 20.0f ;
		Alpha->playerY += Alpha->dy * deltaTime;

		if (Alpha->playerY < Alpha->Height)
		{
			Alpha->playerY = Alpha->Height;
			for (unsigned int i = 0; i < Platform->NO_OF_PLATFORM; ++i)
			{
				Platform->platformPos[i].y -= Alpha->dy * deltaTime;
				land_posy -= Alpha->dy * deltaTime * 0.15f ;
				if (i == landing_ind) {
					landing->position = Platform->platformPos[i];
				}
				if (Platform->platformPos[i].y > windowHeight)
				{
					if (!Platform->enabled[i])
						Platform->pass[i] = true;
					Platform->platformPos[i].y = Platform->platformPos[(i+1)% Platform->NO_OF_PLATFORM].y - 1040 / Platform->NO_OF_PLATFORM;
					Platform->platformPos[i].x = (rand() % (720 - (int)Platform->platform.GetSize().x)) + Platform->platform.GetSize().x / 2;
				}
			}
			for (unsigned int i = 0; i < 3; ++i)
			{
				background_posy[i] -= Alpha->dy * deltaTime * 0.1f;
				if (background_posy[i] >= windowHeight) 
					background_posy[i] = background_posy[(i-1)%3] - 1040.0f;
				background[i].setPosition(Vector2f(0, background_posy[i]));
			}
		}

		for (unsigned int i = 0; i < Platform->NO_OF_PLATFORM; ++i)
		{
			float change = 0.0f;
			if ((Platform->enabled[i] || !Platform->pass[i]) && Alpha->CheckCollision(Platform->platformPos[i], Platform->platform.GetSize() / 2.0f) && Alpha->dy > 0.0f)
			{
				landing->tangKhaTuaPlae = false;
				landing->position = Platform->platformPos[i];
				landing_ind = i;
				sound.play();
				change = max(change, 1700.0f);
			}

			if (Power->CheckCollision(Alpha->player.GetPosition(), Alpha->player.GetSize() / 2.0f)) {
				pw.play();
				Power->state = 0;
				change = max(change, 4000.0f);
			}

			if (change) {
				Alpha->dy = 0.0f;
				Alpha->dy -= change;
			}
		}

		if (CoinP->CheckCollision(Alpha->player.GetPosition(), Alpha->player.GetSize() / 2.0f)) {
			coin.play();
			CoinP->state = 0;
			MoneyPickup+=10;
		}

		if (Alpha->playerY > 1040)
		{
			dead.play();
			SetTextCenter(scoreText);
			SetTextCenter(money);
			scoreText.setPosition(-200, 800);
			money.setPosition(-200, 930);
			
			gstate = 2;
		}

		float speed = (float)difficulty / (float)Platform->NO_OF_PLATFORM;
		Alpha->Update(deltaTime, (speed * (1 - finalspeed_rate)) , curlevel);
		Power->Update(deltaTime);
		CoinP->Update(deltaTime);
		landing->Update(deltaTime);
		land->SetPosition(360 , land_posy);
	}
	else if (gstate == 2) // Game Over
	{
		if (score / score_rate > highscore) {
			highscore = score / score_rate;
			highscoreText.setString("Highscore: " + std::to_string(highscore));
		}
		SetTextCenter(highscoreText);
		if (scoreText.getPosition().x < 360.0f)
			scoreText.move(Vector2f(500.0f, 0.0f) * deltaTime);
		if (highscoreText.getPosition().x < 360.0f)
			highscoreText.move(Vector2f(500.0f, 0.0f) * deltaTime);
		if (money.getPosition().x < 360.0f)
			money.move(Vector2f(500.0f, 0.0f) * deltaTime);
		if (FadeCnt < 255.0f / FadeRate)
		{
			YOUDIED.setColor(Color::Color(255, 255, 255, FadeCnt * FadeRate));
			FadeCnt++;
		}
		/*if (key["SPACE"])
		{
			music.stop();
			gstate = -1;
			pet.money += Money + MoneyPickup;
			pass = true;
			*maingame_state = 1;
			
		}*/
	}
	else if (gstate == 3) {	// Background Customization
		BGMenu[1]->SetPos(Vector2f(360.0f, 520.0f));
		BGMenu[0]->SetPos(Vector2f(-150.0f, 520.0f));
		BGMenu[2]->SetPos(Vector2f(870.0f, 520.0f));
		/*if (key["B"])
		{
			sound.play();
			gstate = 0;
		}*/
		InitBGMenu();
		/*if (key["SPACE"]) {
			if (unlocklvl[equip] <= highscore) {
				equipnow = equip;
				InitBG();
			}
			else
				sound.play();
		}*/
	}
}

void Doodle::Draw(RenderWindow& window)
{

	if (*maingame_state != 2)
		return;
	
	for (int i = 0; i < 3; ++i)
		window.draw(background[i]);
	land->Draw(window);

	if (gstate == 0)
	{
		window.draw(Logo1);
		window.draw(Logo2);

		Alpha->player.Draw(window);
	}
	if (gstate == 1)
	{
		
		Platform->Draw(window, difficulty);
		window.draw(scoreText);
		window.draw(money);
		Power->Draw(window);
		CoinP->Draw(window);
		Alpha->player.Draw(window);
	}
	if (gstate == 2)
	{
		window.clear(Color::White);
		window.draw(YOUDIED);
		window.draw(scoreText);
		window.draw(highscoreText);
		window.draw(money);
	}

	if (gstate == 3) {
		BGMenu[1]->Draw(window);
		BGMenu[0]->Draw(window);
		BGMenu[2]->Draw(window);
		window.draw(SelectBG);
		if (unlocklvl[equip] > highscore) {
			window.draw(unlocked);
			window.draw(Lock);
		}
			
	}

	landing->Draw(window);
}

void Doodle::InitBG()
{
	if (background.empty()) {
		for (int i = 0; i < 3; ++i)
		{
			Sprite A;
			backgroundT.loadFromFile("Assets/Textures/bgex" + std::to_string(equipnow) + ".png");
			A.setTexture(backgroundT);
			A.setScale(Vector2f(windowWidth / backgroundT.getSize().x, windowHeight / backgroundT.getSize().y));
			background.push_back(A);
			background_posy.push_back(i * -1040.0f);
		}
	}
	else {
		for (int i = 0; i < 3; ++i)
		{
			Sprite A;
			backgroundT.loadFromFile("Assets/Textures/bgex" + std::to_string(equipnow) + ".png");
			A.setTexture(backgroundT);
			A.setScale(Vector2f(windowWidth / backgroundT.getSize().x, windowHeight / backgroundT.getSize().y));
			background[i] = A;
			background_posy[i] = i * -1040.0f;
		}
	}
}

void Doodle::SetSpriteCenter(Sprite& S)
{
	FloatRect bound = S.getLocalBounds();
	S.setOrigin(Vector2f(bound.left + bound.width / 2.0f, bound.top + bound.height / 2.0f));
}

void Doodle::SetTextCenter(Text& T)
{
	FloatRect bound = T.getLocalBounds();
	T.setOrigin(Vector2f(bound.left + bound.width / 2.0f, bound.top + bound.height / 2.0f));
}

void Doodle::muteBGM(bool mute)
{
	if (mute)
		music.setVolume(0.0f);
	else
		music.setVolume(15.0f);
}

void Doodle::muteSFX(bool mute)
{
	if (mute) {
		sound.setVolume(0.0f);
		pw.setVolume(0.0f);
		dead.setVolume(0.0f);
		coin.setVolume(0.0f);
	}
	else {
		sound.setVolume(15.0f);
		pw.setVolume(15.0f);
		dead.setVolume(15.0f);
		coin.setVolume(15.0f);
	}
}

void Doodle::InitSound(float musicVolume, float soundVolume)
{
	soundB.loadFromFile("Assets/Sounds/Jump.wav");
	sound.setBuffer(soundB);
	musicB.loadFromFile("Assets/Sounds/indihome.wav");
	music.setBuffer(musicB);
	pwB.loadFromFile("Assets/Sounds/PowerUp.wav");
	pw.setBuffer(pwB);
	deadB.loadFromFile("Assets/Sounds/SlowedOOF.wav");
	dead.setBuffer(deadB);
	coinB.loadFromFile("Assets/Sounds/Pickup_Coin.wav");
	coin.setBuffer(coinB);

	music.setLoop(true);
	
	music.setVolume(musicVolume);
	sound.setVolume(soundVolume);
	pw.setVolume(soundVolume);
	dead.setVolume(100);
	coin.setVolume(soundVolume);
}

void Doodle::InitBGMenu()
{
	if (equip > no_pic)
		equip = 1;
	if (equip < 1)
		equip = no_pic;
	int equipR = 0;
	int equipL = 0;
	if (equip + 1 > no_pic)
		equipR = 1;
	else
		equipR = equip + 1;
	if (equip - 1 < 1)
		equipL = no_pic;
	else
		equipL = equip - 1;
	if (BGMenu.empty()) {
		BGMenu.push_back(new BlockBP("Assets/Textures/bgex" + std::to_string(equip) + ".png"));
		BGMenu.push_back(new BlockBP("Assets/Textures/bgex" + std::to_string(equipR) + ".png"));
		BGMenu.push_back(new BlockBP("Assets/Textures/bgex" + std::to_string(equipL) + ".png"));
	}
	else {
		BGMenu[1]->Object.SetTexture("Assets/Textures/bgex" + std::to_string(equip) + ".png");
		BGMenu[0]->Object.SetTexture("Assets/Textures/bgex" + std::to_string(equipL) + ".png");
		BGMenu[2]->Object.SetTexture("Assets/Textures/bgex" + std::to_string(equipR) + ".png");
	}
	unlocked.setFont(font);
	unlocked.setString("Get < Highscore: " + to_string(unlocklvl[equip]) + " > to unlock.");
	FloatRect bound = unlocked.getLocalBounds();
	unlocked.setOrigin(Vector2f(bound.left + bound.width / 2.0f, bound.top + bound.height / 2.0f));
	unlocked.setPosition(Vector2f(360.0f, 520.0f));
	unlocked.setOutlineColor(Color::Black);
	unlocked.setOutlineThickness(2.0f);
	unlocked.setScale(Vector2f(0.7f,0.7f));
}

void Doodle::InitSprite()
{
	Logo1T.loadFromFile("Assets/Textures/DoodleLogo1.png");
	Logo2T.loadFromFile("Assets/Textures/DoodleLogo2.png");
	Logo1.setTexture(Logo1T);
	Logo2.setTexture(Logo2T);
	SetSpriteCenter(Logo1);
	SetSpriteCenter(Logo2);
	Logo1.setScale(Vector2f(7.0f, 7.0f));
	Logo2.setScale(Vector2f(7.0f, 7.0f));

	YOUDIEDT.loadFromFile("Assets/Textures/GAMEOVER.png");
	YOUDIED.setTexture(YOUDIEDT);
	YOUDIED.setScale(Vector2f(10.0f, 10.0f));
	SetSpriteCenter(YOUDIED);

	SelectBGT.loadFromFile("Assets/Textures/SelectBG.png");
	SelectBG.setTexture(SelectBGT);
	SetSpriteCenter(SelectBG);
	SelectBG.setScale(Vector2f(8.0f, 8.0f));
	SelectBG.setPosition(Vector2f(360.0f, 100.0f));

	LockT.loadFromFile("Assets/Textures/Lock.png");
	Lock.setTexture(LockT);
	SetSpriteCenter(Lock);
	Lock.setScale(Vector2f(6.0f, 6.0f));
	Lock.setPosition(Vector2f(360.0f, 440.0f));

}

void Doodle::InitText()
{
	font.loadFromFile("Assets/Fonts/Minecraftia.ttf");

	scoreText.setFont(font);
	scoreText.setOutlineThickness(2.0f);
	scoreText.setOutlineColor(Color::Black);
	scoreText.setCharacterSize(50);
	scoreText.setFillColor(Color::Red);
	scoreText.setString("Score: " + std::to_string(score));

	highscoreText.setFont(font);
	highscoreText.setOutlineThickness(2.0f);
	highscoreText.setOutlineColor(Color::Black);
	highscoreText.setCharacterSize(50);
	highscoreText.setFillColor(Color::Red);
	highscoreText.setString("Highscore: " + std::to_string(highscore));

	money.setFont(font);
	money.setOutlineThickness(2.0f);
	money.setOutlineColor(Color::Black);
	money.setCharacterSize(50);
	money.setFillColor(Color::Yellow);
	money.setString("Money: " + std::to_string(Money));

}