#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
namespace Config
{
	//-------------------MAIN SETTINGS-----------------------------
	const Uint32 SDL_INIT_FLAGS = SDL_INIT_VIDEO;
	const int IMG_INIT_FLAGS = IMG_INIT_PNG;
	const char * const WINDOW_TITLE = "Super Mario Bros";
	const int TEXTURE_FILE_NAME_LENGTH = 128;





	//-------------------DISPLAY SETTINGS--------------------------
	const Uint16 SCREEN_WIDTH = 600;
	const Uint16 SCREEN_HEIGHT = 600;

	const int WINDOW_POSITION = SDL_WINDOWPOS_UNDEFINED;
	const Uint32 WINDOW_FLAGS = SDL_WINDOW_FULLSCREEN_DESKTOP;
	const Uint32 RENDERER_FLAGS = SDL_RENDERER_ACCELERATED;// | SDL_RENDERER_PRESENTVSYNC;
	const int RENDERER_DRIVER_INDEX = -1;

	const bool FPS_LOCK = false;
	const int FRAMERATE = 60;
	const int CURRENT_FPS_UPDATE_INTERVAL = 30;//Interval between the following FPS measurements
	const double VSYNC_REQUIRED_FRAME_TIME = 1000.f / (double)FRAMERATE;

	const char * const FONT = "OpenSans.ttf";






	//-------------------GAME SETTINGS----------------------------
	//Player speed in pixels per second
	const int PLAYER_SPEED = 400;
	const int JUMP_HIGHT = 200;
	const int LEVEL_WIDTH = 2000;
	const int LEVEL_HEIGHT = 600;



	

	



}
