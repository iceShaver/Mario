#pragma once
#include "Timer.h"
#include <SDL_ttf.h>
#include "List.h"
#include "Object.h"
#include <SDL.h>
#include "FPSGauge.h"
#include "Player.h"
#include "Background.h"

class Program
{
public:
	static FPSGauge fpsGauge;
	static Timer timer;
	static bool Init();
	static bool LoadContent();
	static void Render();
	static void Exit();
	static void EmergencyExit();
	static void HandleEvent();
	static void HandleAction();
	static void ClearRenderer();
	static bool quit;
	static SDL_Renderer * renderer;
	static TTF_Font * font;
	static Player * player;
	static Background * background;
	static int deltaTime;

private:
	static SDL_Window * window;
	static SDL_Event event;
	static List<Object> objects;
};

