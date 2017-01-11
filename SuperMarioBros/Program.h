#pragma once
#include "Timer.h"
#include <SDL_ttf.h>
#include "List.h"
#include "Object.h"
#include <SDL.h>
#include "FPSGauge.h"
class Program
{
public:
	static FPSGauge fpsGauge;
	static Timer timer;
	static bool Init();
	static bool LoadContent();
	static void Exit();
	static void EmergencyExit();
	static void HandleEvent();
	static void HandleAction();
	static void ClearRenderer();
	static bool quit;
	static SDL_Renderer * renderer;
	static TTF_Font * font;

private:
	static SDL_Window * window;
	static SDL_Event event;
	static int deltaTime;
	static List<Object> objects;
};

