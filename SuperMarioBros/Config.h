#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

namespace Config
{
	struct Color
	{
		Uint8 R, G, B;
	};
	//-------------------MAIN SETTINGS-----------------------------
	const Uint32 SDL_INIT_FLAGS = SDL_INIT_VIDEO;
	const int IMG_INIT_FLAGS = IMG_INIT_PNG;
	const char * const WINDOW_TITLE = "Super Mario Bros";
	const int TEXTURE_FILE_NAME_LENGTH = 128;
	const int LEVEL_NAME_LENGTH = 256;
	const int LEVEL_FILE_PATH_LENGTH = 256;
	const int OBJECT_NAME_LENGTH = 256;





	//-------------------DISPLAY SETTINGS--------------------------
	const Uint16 SCREEN_WIDTH = 600;
	const Uint16 SCREEN_HEIGHT = 600;

	const int WINDOW_POSITION = SDL_WINDOWPOS_UNDEFINED;
	const Uint32 WINDOW_FLAGS = SDL_WINDOW_SHOWN;
	const Uint32 RENDERER_FLAGS = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	const int RENDERER_DRIVER_INDEX = -1;

	const bool FPS_LOCK = false;
	const int FRAMERATE = 60;
	const int CURRENT_FPS_UPDATE_INTERVAL = 30;//Interval between the following FPS measurements
	const double VSYNC_REQUIRED_FRAME_TIME = 1000.f / static_cast<double>(FRAMERATE);

	const char * const STANDARD_FONT = "fonts/OpenSans.ttf";
	const int STANDARD_FONT_SIZE = 11;
	const char * const GAME_FONT = "fonts/FreckleFace.ttf";
	const int GAME_FONT_SIZE = 30;
	const Color INFO_FONT_COLOR = { 0,0,0 };
	const Color MENU_FONT_COLOR = { 0xff,0xff,0xff };





	//-------------------GAME SETTINGS----------------------------
	
	const int PLAYER_SPEED = 500; //Player speed in pixels per second
	const int JUMP_HIGHT = 200; //Jump high in pixels
	const int INITIAL_LIVES_COUNT = 3;



	

	



}
