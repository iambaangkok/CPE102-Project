#include "ParticleSystem.h"
ParticleSystem::ParticleSystem() {

}
ParticleSystem::ParticleSystem(float rate, float spread, float angleOngsa, float lifetime, float speed
, Vector2f dimensions, Vector2f position, string texturePath, Vector2u imageCount, Vector2i start, Vector2i finish, float frameTime, float floorLine, float whelaTheePloyThangMod, bool burst, bool gravity_on) {
	this->rate = rate;
	this->spread = spread;
	this->angleDegree = angleOngsa;

	while (this->angleDegree > 360)
	{
		this->angleDegree = this->angleDegree - 360;
	}
	this->lifetime = lifetime;
	this->speed = speed;
	this->position = position;
	
	this->gravity_on = gravity_on;
	this->floorLine = floorLine;
	this->burst = burst;
	this->whelaTheePloyThangMod = whelaTheePloyThangMod;
	static GameObject emitter = GameObject(position, dimensions, true, texturePath
	, imageCount, start, finish , frameTime);
	
	

	numberOfParticle = rate * lifetime;
	minAngle = angleOngsa - spread;
	
	while (minAngle > 360)
	{
		minAngle = minAngle - 360;
	}
	maxAngle = angleOngsa + spread;
	
	while (maxAngle > 360)
	{
		maxAngle = maxAngle - 360;
	}
	angleDiff = maxAngle - minAngle;

	for (int i = 0; i < numberOfParticle; ++i) {
		amountOfParticle.push_back(emitter);
		float randAngle;
		if (spread != 0) {
			randAngle = rand() % angleDiff + minAngle;
		}
		else
		{
			randAngle = angleOngsa;
		}
		randedAngle.push_back(randAngle);
		totalTime.push_back(lifetime);
		started.push_back(0);
	}
	
	spawnTime = 1/rate;
	currentParticle = 0;
	currentSpawnTime = 0;
	loopCount = 0;
	whelaTheePloyThangMod = -1;


	
	for (int i = 0; i < numberOfParticle; ++i)
	{
		angleOngsa = randedAngle[i];
		angleRadian = angleOngsa * (3.1415926 / 180);
		float speedx = speed * cos(angleRadian);
		float speedy = speed * sin(angleRadian);
		vectorspeedX.push_back(speedx);
		vectorspeedY.push_back(speedy);
	}

}

int ParticleSystem::Update(float deltaTime) {
	totalTimein1spawn = totalTimein1spawn + deltaTime;
	if (spawning_on == true) {
		currentSpawnTime = currentSpawnTime + deltaTime;
		
	}
	if (totalTimein1spawn >= whelaTheePloyThangMod) {
		spawning_on = false;
	}
	/*if (spawning_on == false) {
		for (int i = 0; i < numberOfParticle) {
			amountOfParticle[j].SetPosition(position);
		}
	}*/
	if (burst == true) {
		if (!tangKhaTuaPlae) {
			for (int i = 0; i < numberOfParticle; ++i) {
				started[i] = true;
				amountOfParticle[i].SetPosition(position);
				totalTime[i] = lifetime;
				float randAngle;
				if (spread != 0) {
					randAngle = rand() % angleDiff + minAngle;
				}
				else
				{
					randAngle = angleDegree;
				}
				randedAngle[i] = randAngle;
				angleDegree = randedAngle[i];
				angleRadian = angleDegree * (3.1415926 / 180);
				float speedx = speed * cos(angleRadian);
				float speedy = speed * sin(angleRadian);
				vectorspeedX[i] = speedx;
				vectorspeedY[i] = speedy;
			}
			tangKhaTuaPlae = true;
		}
		for (int i = 0; i < numberOfParticle; ++i) {
			if (started[i] == true) {
				currentParticle = i;
				/*if (gravity_on == true) {
					vectorspeedY[i] = vectorspeedY[i] + gravity * deltaTime;
				}*/
				Move();
				if (amountOfParticle[i].GetPosition().y + amountOfParticle[i].GetDimensions().y / 2 >= floorLine) {
					vectorspeedY[i] = 0;
					amountOfParticle[i].SetPosition(amountOfParticle[i].GetPosition().x, floorLine - amountOfParticle[i].GetDimensions().y / 2);
				}
				totalTime[i] = totalTime[i] - deltaTime;
			}
		}
	}
	else if(burst == false) {
		for (int i = 0; i < numberOfParticle; ++i) {
			if (currentSpawnTime < (i + 1) * spawnTime && currentSpawnTime >(i) * spawnTime) {//&& !started[i]) {//currentSpawnTime >= (i)*spawnTime && !started[i]) {

				//cout << i << ": " << (i)*spawnTime << " " << currentSpawnTime << " " << (i + 1) * spawnTime << endl;
				//cout << "STARTED" << endl;int j = i;
				for (int j = i; j > lastSpawnedParticle && j >= 0; --j) {
					started[j] = true;
					amountOfParticle[j].SetPosition(position);
					totalTime[j] = lifetime;
					float randAngle;
					if (spread != 0) {
						randAngle = rand() % angleDiff + minAngle;
					}
					else
					{
						randAngle = angleDegree;
					}
					randedAngle[j] = randAngle;
					angleDegree = randedAngle[j];
					angleRadian = angleDegree * (3.1415926 / 180);
					float speedx = speed * cos(angleRadian);
					float speedy = speed * sin(angleRadian);
					vectorspeedX[j] = speedx;
					vectorspeedY[j] = speedy;
				}


				lastSpawnedParticle = i;
			}
			else
			{
				//cout << "" << endl;

			}
			if (started[i] == true) {
				currentParticle = i;
				if (gravity_on == true) {
					vectorspeedY[i] = vectorspeedY[i] + gravity * deltaTime;
				}
				Move();
				if (amountOfParticle[i].GetPosition().y + amountOfParticle[i].GetDimensions().y / 2 >= floorLine) {
					vectorspeedY[i] = 0;
					amountOfParticle[i].SetPosition(amountOfParticle[i].GetPosition().x, floorLine - amountOfParticle[i].GetDimensions().y / 2);
				}
				totalTime[i] = totalTime[i] - deltaTime;
			}
		}
	}
	for (int i = 0; i < numberOfParticle; ++i) {
		//if (spawning_on == true) {
			if (totalTime[i] <= 0) {
				started[i] = false;
			}
		//}
	}

	if (currentSpawnTime > spawnTime * numberOfParticle) {
		currentSpawnTime -= spawnTime * numberOfParticle;
	}

	if (totalTimein1spawn >= whelaTheePloyThangMod + lifetime) {
		return 1;
	}
	return 0;

}

void ParticleSystem::Draw(RenderWindow& window) {
	for (int i = 0; i < numberOfParticle; ++i) {
		if (started[i] == 1) {
			amountOfParticle[i].Draw(window);
		}
	}
	


}

void ParticleSystem::Move() {
	amountOfParticle[currentParticle].Move(vectorspeedX[currentParticle], vectorspeedY[currentParticle]);
	if(currentParticle < numberOfParticle){
			currentParticle++;
	}
}

ParticleSystem::~ParticleSystem() {
	cout << "ParticleSystem deleted";
}