#pragma once
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <setjmp.h>
#include <signal.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Timer.h"
#include "FPSGauge.h"


namespace Config
{
	const Uint16 SCREEN_WIDTH = 640;
	const Uint16 SCREEN_HEIGHT = 480;
	const Uint32 SDL_INIT_FLAGS = SDL_INIT_VIDEO;
	const int IMG_INIT_FLAGS = IMG_INIT_PNG;
	const char * const WINDOW_TITLE = "Super Mario Bros";
	const int WINDOW_POSITION = SDL_WINDOWPOS_UNDEFINED;
	const Uint32 WINDOW_FLAGS = SDL_WINDOW_SHOWN;
	const int RENDERER_DRIVER_INDEX = -1;
	const Uint32 RENDERER_FLAGS = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	//Interval between the following FPS measurements
	const int CURRENT_FPS_UPDATE_INTERVAL = 30;



}
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
};

