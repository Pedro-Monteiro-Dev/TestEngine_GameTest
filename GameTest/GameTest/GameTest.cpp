#include<engine.h>

#undef main

GameEngine::Engine engine;
Input input;

float globalRotation = -90.0f;

class Enemy : public GameObject {
public:
	int healthPoints = 1;

	float damageFeedbackTimer = 0;
	float damageFeedbackDuration = 5;
	float damageFeedbackSpeed = 2;

	void showDamageFeedback() {
		modulate.r = 255;
		modulate.g = 0;
		modulate.b = 0;
	}

	void hideDamageFeedback() {
		modulate.r = 255;
		modulate.g = 255;
		modulate.b = 255;
	}

	void checkDamageFeedback() {
		if (damageFeedbackTimer > 0) {
			damageFeedbackTimer -= damageFeedbackDuration * damageFeedbackSpeed * engine.deltaTime;

			if (int(damageFeedbackTimer) % 2 == 0) {
				showDamageFeedback();
			}
			else {
				hideDamageFeedback();
			}

		}
		else
		{
			hideDamageFeedback();
			damageFeedbackTimer = 0;
		}
	}

	void TakeDamage(int paramFirePower) {
		healthPoints -= paramFirePower;

		

		if (healthPoints <= 0) {
			Destroy();

		}
		else {
			
			showDamageFeedback();
			damageFeedbackTimer = damageFeedbackDuration;
			
		}
	}

};

class explosion : public GameObject {
public:
	
	void OnStart() override {

		int textureDimentions[2] = { 5,2 };

		animation = Animation("resources/graphics/explode64.bmp", 0.1f, textureDimentions, false, {});
	}

	void OnAnimationFinish() override {
		Destroy();
	}

};


class missile : public GameObject {
public:
	float moveSpeed = 200.0f;

	int firePower = 0;
	int missileDamage = 1;

	void OnStart() override {
		int textureDimentions[2] = { 2,3 };

		switch (firePower) {
		case 0:
			animation = Animation("resources/graphics/missile.bmp", 0.1f, textureDimentions, true, { AnimationCoord(0,0),AnimationCoord(1,0) });
			break;
		case 1:
			animation = Animation("resources/graphics/missile.bmp", 0.1f, textureDimentions, true, { AnimationCoord(0,1),AnimationCoord(1,1) });
			break;
		case 2:
			animation = Animation("resources/graphics/missile.bmp", 0.1f, textureDimentions, true, { AnimationCoord(0,2),AnimationCoord(1,2) });
			break;
		default:
			animation = Animation("resources/graphics/missile.bmp", 0.1f, textureDimentions, true, { AnimationCoord(0,0),AnimationCoord(1,0) });
		}

		collisionBoxSize.w = collisionBoxSize.h = 16.0f;

		objectGroup = "bullet";

		rotation = globalRotation;

	}

	int getMissileDamage() {
		int damage = 1;

		switch (firePower) {
		case 0:
			damage = 1;
			break;
		case 1:
			damage = 2;
			break;
		case 2:
			damage = 4;
			break;

		}

		return damage;
	}

	void OnUpdate() override {
		//float delta = engine.deltaTime;
		position.x -= moveSpeed * engine.deltaTime;
		//std::cout << position.y <<"\n";

		if (position.x < -32) {
			Destroy();
		}

		//position.x -= moveSpeed * engine.getDeltaTime();
	}

};

class rusher : public Enemy {
public:
	float moveSpeed = 150.0f;
	void OnStart() override {

		healthPoints = 2;

		int textureDimentions[2] = { 4,6 };

		animation = Animation("resources/graphics/rusher.bmp", 0.05f, textureDimentions, true, {});
		objectGroup = "enemy";

		collisionBoxSize.w = 64.0f;
		collisionBoxSize.h = 32.0f;

		rotation = globalRotation;
	}

	void OnUpdate() override {
		
		/* Classic Movement
		position.y += moveSpeed * engine.deltaTime;

		if (position.y > 480) {
			Destroy();
		}
		*/

		position.x += moveSpeed * engine.deltaTime;

		if (position.x > 640) {
			Destroy();
		}

		checkDamageFeedback();
	}

	void OnCollideEnter(GameObject& contact) override {
		//engine.print("Collide");
		if (contact.objectGroup == "bullet") {
			


			explosion* boom = new explosion();
			boom->position.x = position.x;
			boom->position.y = position.y;
			engine.getLevel().addObject(boom);

			if (missile* missileContact = dynamic_cast<missile*>(&contact)) {

				int missileFirePower = missileContact->getMissileDamage();
				//int missileFirePower = missileContact->firePower + 1;

				TakeDamage(missileFirePower);
			}

			contact.Destroy();
			//Destroy();
			
		}
	}
	
};

class drone : public Enemy {
public:
	float moveSpeed = 60.0f;
	float sinOffset = 0.0f;
	int packID = 0;

	void OnStart() override {

		healthPoints = 1;

		int textureDimentions[2] = { 8,2 };

		animation = Animation("resources/graphics/drone.bmp", 0.1f, textureDimentions, true, {});
		objectGroup = "enemy";

		//(packID * 0.1)

		sinOffset += (packID *32);
	}

	void OnUpdate() override {

		position.x += moveSpeed * engine.deltaTime;

		sinOffset += 2 * engine.deltaTime;
		position.y = position.y - sin(sinOffset);


		if (position.x > 640) {
			Destroy();
		}

		checkDamageFeedback();

		//std::cout << sin(sinOffset) << "\n";
	}

	void OnCollideEnter(GameObject& contact) override {
		//engine.print("Collide");
		if (contact.objectGroup == "bullet") {

			explosion* boom = new explosion();
			boom->position.x = position.x;
			boom->position.y = position.y;
			engine.getLevel().addObject(boom);

			if (missile* missileContact = dynamic_cast<missile*>(&contact)) {

				int missileFirePower = missileContact->getMissileDamage();

				TakeDamage(missileFirePower);
			}

			contact.Destroy();
			//Destroy();

		}
	}

};

class enemyProjectile : public GameObject {
public:
	float moveSpeed = 200.0f;


	void OnStart() override {
		int textureDimentions[2] = { 8,1 };

		animation = Animation("resources/graphics/EnWeap6.bmp", 0.1f, textureDimentions, true, {});
		objectGroup = "enemyBullet";

		collisionBoxSize.w = collisionBoxSize.h = 16.0f;
	}

	void OnUpdate() override {
		//float delta = engine.deltaTime;
		position.x += moveSpeed * engine.deltaTime;
		//std::cout << position.y <<"\n";

		
		if (position.y > 640) {
			Destroy();
		}
		//position.x -= moveSpeed * engine.getDeltaTime();
	}

};

class metalAsteroid : public GameObject {
public:
	float moveSpeed = 60.0f;
	int asteroidSize = 32;

	void OnStart() override {

		//int textureDimentions[2];
		int textureDimentions[2] = { 8,2 };
		animation = Animation("resources/graphics/MAster32.bmp", 0.1f, textureDimentions, true, {});
		
		switch (asteroidSize) {
			case 64:
				textureDimentions[0] = 8;
				textureDimentions[1] = 3;
				animation = Animation("resources/graphics/MAster64.bmp", 0.1f, textureDimentions, true, {});
				break;
			case 96:
				textureDimentions[0] = 5;
				textureDimentions[1] = 5;
				animation = Animation("resources/graphics/MAster96.bmp", 0.1f, textureDimentions, true, {});
				break;
			default:
				textureDimentions[0] = 8;
				textureDimentions[1] = 2;
				animation = Animation("resources/graphics/MAster32.bmp", 0.1f, textureDimentions, true, {});
		}
		
		collisionBoxSize.w = collisionBoxSize.h = asteroidSize;
		rotation = globalRotation;
	}

	void OnUpdate() override {
		position.x += moveSpeed * engine.deltaTime;

		if (position.x > 640) {
			Destroy();
		}

	}

	void OnCollideEnter(GameObject& contact) override {
		
		if (contact.objectGroup == "bullet") {
			contact.Destroy();
			
		}
	}


};

class stoneAsteroid : public Enemy {
public:
	//float moveSpeed = 60.0f;

	struct
	{
		float x = 60.0f;
		float y = 0.0f;
	}moveSpeed;

	int asteroidSize = 32;

	void OnStart() override {

		int textureDimentions[2];

		switch (asteroidSize) {
			case 64:
				healthPoints = 3;

				textureDimentions[0] = 8;
				textureDimentions[1] = 3;
				animation = Animation("resources/graphics/SAster64.bmp", 0.1f, textureDimentions, true, {});
				break;
			case 96:
				healthPoints = 6;

				textureDimentions[0] = 5;
				textureDimentions[1] = 5;
				animation = Animation("resources/graphics/SAster96.bmp", 0.1f, textureDimentions, true, {});
				break;
			default:
				healthPoints = 1;

				textureDimentions[0] = 8;
				textureDimentions[1] = 2;
				animation = Animation("resources/graphics/SAster32.bmp", 0.1f, textureDimentions, true, {});
		}

		collisionBoxSize.w = collisionBoxSize.h = asteroidSize;
		//objectGroup = "bullet";
		rotation = globalRotation;
	}

	void OnDestroyed() override {
		stoneAsteroid* asteroid1 = new stoneAsteroid();
		stoneAsteroid* asteroid2 = new stoneAsteroid();

		switch (asteroidSize) {
			case 64:

				asteroid1->position.x = position.x;
				asteroid1->position.y = position.y;
				asteroid1->asteroidSize = 32;
				asteroid1->moveSpeed.y = 32.0f;

				asteroid2->position.x = position.x;
				asteroid2->position.y = position.y;
				asteroid2->asteroidSize = 32;
				asteroid2->moveSpeed.y = -32.0f;

				engine.getLevel().addObject(asteroid1);
				engine.getLevel().addObject(asteroid2);

				break;
			case 96:

				asteroid1->position.x = position.x;
				asteroid1->position.y = position.y;
				asteroid1->asteroidSize = 64;
				asteroid1->moveSpeed.y = 32.0f;

				asteroid2->position.x = position.x;
				asteroid2->position.y = position.y;
				asteroid2->asteroidSize = 64;
				asteroid2->moveSpeed.y = -32.0f;

				engine.getLevel().addObject(asteroid1);
				engine.getLevel().addObject(asteroid2);
				break;
			default:

				break;
		}

	}

	void OnUpdate() override {
		
		position.x += moveSpeed.x * engine.deltaTime;
		position.y += moveSpeed.y * engine.deltaTime;

		if (position.x > 640) {
			Destroy();
		}

		checkDamageFeedback();

		//position.x -= moveSpeed * engine.getDeltaTime();
	}

	void OnCollideEnter(GameObject& contact) override {

		if (contact.objectGroup == "bullet") {
			
			stoneAsteroid* asteroid1 = new stoneAsteroid();
			stoneAsteroid* asteroid2 = new stoneAsteroid();

			switch (asteroidSize) {
				case 64:

					if (missile* missileContact = dynamic_cast<missile*>(&contact)) {

						int missileFirePower = missileContact->getMissileDamage();

						TakeDamage(missileFirePower);
					}

					contact.Destroy();
					
					//TakeDamage(contact.firePower);


					//Destroy();
										
					break;
				case 96:

					if (missile* missileContact = dynamic_cast<missile*>(&contact)) {

						int missileFirePower = missileContact->getMissileDamage();

						TakeDamage(missileFirePower);
					}

					contact.Destroy();
					//Destroy();
					break;
				default:

					if (missile* missileContact = dynamic_cast<missile*>(&contact)) {

						int missileFirePower = missileContact->getMissileDamage();

						TakeDamage(missileFirePower);
					}

					contact.Destroy();

					//Destroy();
					
			}

			explosion* boom = new explosion();
			boom->position.x = position.x;
			boom->position.y = position.y;
			engine.getLevel().addObject(boom);

		}
	}


};

class loner : public Enemy {
public:
	float moveSpeed = 70.0f;
	float time = 0.0f;
	float timeCooldown = 2.0f;

	void OnStart() override {

		healthPoints = 3;

		int textureDimentions[2] = { 4,4 };

		animation = Animation("resources/graphics/LonerA.bmp", 0.05f, textureDimentions, true, {});
		objectGroup = "enemy";


		collisionBoxSize.w = collisionBoxSize.h = 64.0f;
		//position.x = 50.0f;
		//position.y = 50.0f;
		rotation = globalRotation;
	}

	void OnCollideEnter(GameObject& contact) override {
		//engine.print("Collide");
		if (contact.objectGroup == "bullet") {



			explosion* boom = new explosion();
			boom->position.x = position.x;
			boom->position.y = position.y;
			engine.getLevel().addObject(boom);

			if (missile* missileContact = dynamic_cast<missile*>(&contact)) {

				int missileFirePower = missileContact->getMissileDamage();

				TakeDamage(missileFirePower);
			}

			contact.Destroy();
			//Destroy();

		}
	}

	/*
	void animation.OnAnimationEnd() override {
		std::cout << "Animation end" << std::endl;
	}
	*/


	void OnUpdate() override {
		time += 1 * engine.deltaTime;

		if (time > timeCooldown) {
			enemyProjectile* enemyProj = new enemyProjectile();
			enemyProj->position.x = position.x + 48;
			enemyProj->position.y = position.y + 24;
			engine.getLevel().addObject(enemyProj);

			time = 0;
		}

		position.y += moveSpeed * engine.deltaTime;

		checkDamageFeedback();

		if (position.y > 480) {
			Destroy();
		}

	}

};


class powerUpMissile : public GameObject {
public:
	float moveSpeed = 30.0f;


	void OnStart() override {
		int textureDimentions[2] = { 4,2 };

		//animation = Animation("resources/graphics/LonerA.bmp", 0.05f, textureDimentions, true, {});
		animation = Animation("resources/graphics/PUWeapon.bmp", 0.1f, textureDimentions, true, {});
		objectGroup = "powerUpMissile";

	}

	void OnUpdate() override {
		//float delta = engine.deltaTime;
		//position.y += moveSpeed * engine.deltaTime;
		//std::cout << position.y <<"\n";

		if (position.y > 480) {
			Destroy();
		}

		//position.x -= moveSpeed * engine.getDeltaTime();
	}

};

class powerUpHeal : public GameObject {
public:
	float moveSpeed = 30.0f;


	void OnStart() override {
		int textureDimentions[2] = { 4,2 };

		//animation = Animation("resources/graphics/LonerA.bmp", 0.05f, textureDimentions, true, {});
		animation = Animation("resources/graphics/PUShield.bmp", 0.1f, textureDimentions, true, {});
		objectGroup = "powerUpHeal";

	}

	void OnUpdate() override {
		//float delta = engine.deltaTime;
		//position.y += moveSpeed * engine.deltaTime;
		//std::cout << position.y <<"\n";

		if (position.y > 480) {
			Destroy();
		}

		//position.x -= moveSpeed * engine.getDeltaTime();
	}

};


class spaceship : public Pawn {
public:
	//float moveSpeed = 200.0f;
	
	int shipHealthMax = 5;
	int shipHealth = 5;

	std::string currentAnimation = "";
	int animationState = 0;

	bool keyPressed = false;

	int firePower = 0;

	//Input playerInput;
	//GameEngine::Engine getEngine;

	//SHORT keyStatea = GetKeyState(VK_SPACE);

	void upgradeFirePower() {
		if (firePower < 2) {
			firePower++;
			std::cout << firePower << "\n";
			
		}
	}

	void OnStart() override {
		int textureDimentions[2] = { 7,1 };

		movementSpeed = 200.0f;

		animationState = 0;
		//currentAnimation = "Idle";
		//animation = Animation("resources/graphics/Ship1.bmp",0.1f, textureDimentions, false, {AnimationCoord(3,0)});
		objectGroup = "player";

		position.x = 550.0f;
		position.y = 208.0f;

		collisionBoxSize.w = collisionBoxSize.h = 64.0f;
		rotation = globalRotation;
	}

	void OnUpdate() override {
		
		int textureDimentions[2] = { 7,1 };


		if(GetAsyncKeyState(input.ShootAction[0]) & 0x8000) {
			if (!keyPressed) {
				missile* bullet = new missile();
				bullet->position.x = position.x;
				bullet->position.y = position.y +24;
				bullet->firePower = firePower;
				engine.getLevel().addObject(bullet);

				keyPressed = true;
			}
		}
		else {
			keyPressed = false;
		}

		if (GetKeyState(input.MoveLeft[0]) & 0x8000)
		{
			position.x -= movementSpeed * engine.deltaTime;
		}
		else if (GetKeyState(input.MoveRight[0]) & 0x8000)
		{
			position.x += movementSpeed * engine.deltaTime;

		}
		

		if (GetKeyState(input.MoveUp[0]) & 0x8000)
		{
			position.y -= movementSpeed * engine.deltaTime;
			animationState = 1;
		}
		else if (GetKeyState(input.MoveDown[0]) & 0x8000)
		{
			position.y += movementSpeed * engine.deltaTime;
			animationState = 2;
		}
		else
		{
			animationState = 0;
		}
		
		//std::cout << currentAnimation << "\n";

		if (animationState==1 && currentAnimation != "Up")
		{
			currentAnimation = "Up";
			
			animation = Animation("resources/graphics/Ship1.bmp", 0.1f, textureDimentions, false, { AnimationCoord(4,0),AnimationCoord(5,0),AnimationCoord(6,0) });
			animation.spriteIndex = 0;		
		}
		else if (animationState == 2 && currentAnimation != "Down")
		{
			currentAnimation = "Down";
			animation = Animation("resources/graphics/Ship1.bmp", 0.1f, textureDimentions, false, { AnimationCoord(2,0),AnimationCoord(1,0),AnimationCoord(0,0) });
			animation.spriteIndex = 0;
		}
		else if (animationState == 0 && currentAnimation != "Idle")
		{
			currentAnimation = "Idle";
			animation = Animation("resources/graphics/Ship1.bmp", 0.1f, textureDimentions, false, { AnimationCoord(3,0) });
			animation.spriteIndex = 0;
		}
		//std::cout << currentAnimation << " " << animationState << "\n";
	}

	void TakeShipDamage() {
		shipHealth -= 1;
	}

	void HealShip() {
		int healAmount = 2;

		shipHealth += healAmount;

		if (shipHealth > shipHealthMax) {
			shipHealth = shipHealthMax;
		}
	}

	void OnCollideEnter(GameObject& contact) override {
		//engine.print("Collide");
		if (contact.objectGroup == "enemyBullet") {
			explosion* boom = new explosion();
			boom->position.x = position.x;
			boom->position.y = position.y;
			engine.getLevel().addObject(boom);
			TakeShipDamage();
			contact.Destroy();
		}

		if (contact.objectGroup == "powerUpMissile") {
			upgradeFirePower();
			contact.Destroy();
		}

		if (contact.objectGroup == "powerUpHeal") {
			HealShip();
			contact.Destroy();
		}
	}


};


int main()
{
	//GameWindow gameWindow("Xenon 2000",640,480);

	GameWindow gameWindow;
	gameWindow.windowName = "Xenon 2000";
	gameWindow.windowWidth = 640;
	gameWindow.windowHeight = 480;

	//Game game;

	

	// Input Mapping

	input.ShootAction = { VK_SPACE };
	input.MoveDown = { VK_DOWN };
	input.MoveLeft = { VK_LEFT };
	input.MoveRight = { VK_RIGHT };
	input.MoveUp = { VK_UP };
	
	GameLevel level;

	LevelBackground backgroundLayer1;

	backgroundLayer1.background_path = "resources/graphics/galaxy2.bmp";
	backgroundLayer1.scrollingSpeed = 0;

	LevelBackground backgroundLayer2;

	backgroundLayer2.background_path = "resources/graphics/GAster96.bmp";
	backgroundLayer2.scrollingSpeed = 10;
	backgroundLayer2.scrollingDirection = backgroundLayer2.horizontal;

	//engine.print("print test");

	level.setLayerSize(2);
	level.background[0] = backgroundLayer1;
	level.background[1] = backgroundLayer2;

	engine.setLevel(level);

	spaceship* ship = new spaceship();
	
	rusher* enemyA = new rusher();
	enemyA->position.x = -150.0f;
	enemyA->position.y = 150.0f;

	rusher* enemyB = new rusher();
	enemyB->position.x = -200.0f;
	enemyB->position.y = 200.0f;

	loner* lonerA = new loner();
	lonerA->position.x = 200.0f;
	lonerA->position.y = -50.0f;

	
	metalAsteroid* metalAsteroidA = new metalAsteroid();
	metalAsteroidA->position.x = 0.0f;
	metalAsteroidA->position.y = 250.0f;
	metalAsteroidA->asteroidSize = 96;

	stoneAsteroid* stoneAsteroidA = new stoneAsteroid();
	stoneAsteroidA->position.x = -300.0f;
	stoneAsteroidA->position.y = 100.0f;
	stoneAsteroidA->asteroidSize = 96;

	powerUpMissile* powerUpA = new powerUpMissile();
	powerUpA->position.x = 300.0f;
	powerUpA->position.y = 170.0f;

	powerUpMissile* powerUpB = new powerUpMissile();
	powerUpB->position.x = 350.0f;
	powerUpB->position.y = 180.0f;

	powerUpMissile* powerUpC = new powerUpMissile();
	powerUpC->position.x = 400.0f;
	powerUpC->position.y = 190.0f;

	powerUpHeal* powerUpHealA = new powerUpHeal();
	powerUpHealA->position.x = 450.0f;
	powerUpHealA->position.y = 190.0f;

	engine.getLevel().addObject(ship);

	engine.getLevel().addObject(enemyA);
	engine.getLevel().addObject(enemyB);
	engine.getLevel().addObject(lonerA);

	//engine.getLevel().addObject(metalAsteroidA);
	//engine.getLevel().addObject(stoneAsteroidA);
	

	engine.getLevel().addObject(powerUpA);
	engine.getLevel().addObject(powerUpB);
	engine.getLevel().addObject(powerUpC);
	engine.getLevel().addObject(powerUpHealA);

	//Drone Pack

	for (int i = 0; i < 7; ++i)
	{

		drone* dronePack = new drone();
		dronePack->position.x = 30.0f + (i * 35);
		dronePack->position.y = 350.0f ;
		dronePack->packID = i;

		engine.getLevel().addObject(dronePack);

	}

	

	//camera rotate,
	
	//engine.visibleCollisions = true;

	engine.Initialize(gameWindow);
	

	
}
