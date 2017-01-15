#pragma once
#include "Timer.h"
#include <SDL_ttf.h>
#include "List.h"
#include "Object.h"
#include <SDL.h>
#include "FPSGauge.h"
#include "Player.h"
#include "Camera.h"
#include "Level.h"
#include "Menu.h"



class Program
{
public:
	static FPSGauge fpsGauge;

	static bool Init();
	static bool LoadContent();
	static void Render();
	static void Exit();
	static void EmergencyExit();
	static void HandleEvent();
	static bool EndTime();
	static void CountRemainingTime();
	static void EndGame();
	static void HandleAction();
	static void ClearRenderer();
	static void SetDeltaTime();
	static float GetDeltaTime();
	static void DisplayText(const char * text, int x, int y, Texture::Color color = {0,0,0}, TTF_Font * font = standardFont);
	static void DisplayDiagnosticInfo();
	static void DisplayInfo();
	static void DisplayMenu();
	static void StartTheGame();
	static bool IsGameStarted();
	static bool quit;
	static SDL_Renderer * renderer;
	static TTF_Font * standardFont;
	static TTF_Font * gameFont;
	static Player * player;
	static Object * background;
	static Object * ground;
	static List<Object> objects;
	static List<Texture> textures;
	static List<Level> levels;
	static Timer timer;
	static Camera camera;
	static Level * loadedLevel;
	static Texture * groundTexture;
	static Texture * backgroundTexture;
	static Texture * playerTexture;
	static Texture * wallTexture;
	static Menu * menu;
	//static SDL_Rect camera;
private:
	//Time of one frame in seconds
	static bool gameStarted;
	static float deltaTime;
	static Timer deltaTimer;
	static SDL_Window * window;
	static SDL_Event event;
	static int remainingTime;
};

