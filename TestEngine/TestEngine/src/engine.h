#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <array>
#include <Windows.h>

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

class LevelBackground
{
	public:
		std::string background_path = "";
		float scrollingSpeed = 0;

		enum scrollingDirectionEnum {
			vertical,
			horizontal,
		};

		int scrollingDirection = vertical;

		struct
		{
			//int x = 0;
			//int y = 0;
			float w = 0.0f;
			float h = 0.0f;

			float w2 = 0.0f;
			float h2 = 0.0f;
		}scrollRect;

		

};

class AnimationCoord
{
public:

	struct 
	{
		int x = 0;
		int y = 0;
	}coordPosition;


	AnimationCoord() = default;

	AnimationCoord(int xParam, int yParam) {
		
		coordPosition.x = xParam;
		coordPosition.y = yParam;
		
	}


};


class Animation {
	public:

		std::string tilemapPath = "";
		int textureWidth = 0;
		int textureHeight = 0;
		int frameWidth = 0;
		int frameHeight = 0;

		int spriteIndex = 0;


		float frameTime = 0.0f;

		float frameDuration = 0.1f;
		bool loop = false;

		std::vector <AnimationCoord> manual;

		struct
		{
			int x = 0;
			int y = 0;
			int w = 0;
			int h = 0;
		}animationRect;

		struct
		{
			int w = 0;
			int h = 0;
		}tilemapSize;

		Animation() = default;
		
		Animation(std::string tilemapParam,float frameDurationParam,int tilemapSizeParam[2], bool loopParam, std::vector <AnimationCoord> manualMode) {
			tilemapPath = tilemapParam;
			frameDuration = frameDurationParam;
			tilemapSize.w = tilemapSizeParam[0];
			tilemapSize.h = tilemapSizeParam[1];
			loop = loopParam;
			manual = manualMode;
		}
		
		virtual void OnAnimationEnd() {};
		int GetSpriteWidth();
		
	//private:
		
		

		//resources / graphics / drone.bmp
		
		/*
		Animation(std::string x,bool z) {
			tilemap_path = x;
			loop = z;



		}
		*/

		//frameWidth = textureWidth / 8;
		//frameHeight = textureHeight / 2;
		

		

		/*
		playerRect.x = playerRect.y = 0;
		playerRect.w = frameWidth;
		playerRect.h = frameHeight;
		*/
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

class GameObject
{
	public:
		Animation animation;

		struct{
			float x = 0.0f;
			float y = 0.0f;
		}position;
		
		struct {
			float w = 32.0f;
			float h = 32.0f;
		}collisionBoxSize;

		struct {
			int r = 255;
			int g = 255;
			int b = 255;
		}modulate;

		float rotation = 0;

		bool visible = true;

		virtual void OnStart() {};
		virtual void OnUpdate() {};
		virtual void OnAnimationFinish() {};
		virtual void OnCollideEnter(GameObject& contact) {};
		void Destroy();
		virtual void OnDestroyed() {};

		std::string objectGroup;

		bool toBeDeleted = false;
		
	
};

class Pawn : public GameObject
{
public:
	float movementSpeed = 150.0f;
	/*
	struct {
		float x = 0.0f;
		float y = 0.0f;
	}position;
	*/
};

class GameLevel
{
	public:
		std::vector<GameObject*> levelObjects;
		std::vector<LevelBackground> background;

		void setLayerSize(int layerSize);
		void addObject(GameObject* obj);
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
