#pragma once
#include "Timer.h"
#include <SDL_ttf.h>
#include "List.h"
#include "Object.h"
#include <SDL.h>
#include "FPSGauge.h"
#include "Player.h"


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
	static void HandleAction();
	static void ClearRenderer();
	static void SetDeltaTime();
	static void SetCamera();
	static float GetDeltaTime();
	static bool quit;
	static SDL_Renderer * renderer;
	static TTF_Font * font;
	static Player * player;
	static Object * background;
	static Object * ground;
	static List<Object> objects;
	static Timer timer;
	static SDL_Rect camera;
private:
	//Time of one frame in seconds
	static float deltaTime;

	static Timer deltaTimer;
	static SDL_Window * window;
	static SDL_Event event;
};

