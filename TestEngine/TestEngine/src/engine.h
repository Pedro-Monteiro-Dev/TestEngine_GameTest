#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <array>
#include <Windows.h>

#include "animations.h"
#include "engineobjects.h"
#include "level.h"

/*
class Game {
	
	// (currentTime - prevTime) / 1000.0f;
};
*/

class Input {

public:

	std::vector <SHORT> ShootAction;
	std::vector <SHORT> MoveRight;
	std::vector <SHORT> MoveLeft;
	std::vector <SHORT> MoveUp;
	std::vector <SHORT> MoveDown;

	//Uint8 keyState;

	//const Uint8* keyState;
	void init();
};


class Game {
public:
	//float* deltaTime = nullptr;
	//void setLevel();
	void start();
	//void UpdateDeltaTime();
	//void (*UpdateDeltaTime);

private:
	int prevTime = currentTime;
	int currentTime = 0;
};


class GameWindow
{
	public:
		const char* windowName = "My Game";
		int windowWidth = 640;
		int windowHeight = 480;
};

namespace GameEngine {
	class Engine
	{
		public:
			float deltaTime = 0.0f;

			void setLevel(GameLevel level);
			GameLevel& getLevel();
			void print(std::string printText);

			void Update();
			void Initialize(GameWindow windowSettings);
			
			bool visibleCollisions = false;

		private:
			GameLevel mainLevel;
			GameWindow windowDisplay;
			int prevTime = currentTime;
			int currentTime = 0;

	};

}
