#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
namespace Config
{
	const Uint16 SCREEN_WIDTH = 1280;
	const Uint16 SCREEN_HEIGHT = 1024;
	const Uint32 SDL_INIT_FLAGS = SDL_INIT_VIDEO;
	const int IMG_INIT_FLAGS = IMG_INIT_PNG;
	const char * const WINDOW_TITLE = "Super Mario Bros";
	const char * const FONT = "OpenSans.ttf";
	const int OBJECT_NAME_LENGTH = 128;
	const int WINDOW_POSITION = SDL_WINDOWPOS_UNDEFINED;
	const Uint32 WINDOW_FLAGS = SDL_WINDOW_SHOWN;
	const int RENDERER_DRIVER_INDEX = -1;
	const Uint32 RENDERER_FLAGS = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	//Interval between the following FPS measurements
	const int CURRENT_FPS_UPDATE_INTERVAL = 30;
	const int PLAYER_SPEED = 10;
	const int LEVEL_WIDTH = 1200;
	const int LEVEL_HEIGHT = 600;


}
