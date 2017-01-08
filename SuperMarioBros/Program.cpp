#include "Program.h"
#include <SDL.h>
#include <conio.h>

SDL_Window * Program::window;
SDL_Renderer * Program::renderer;
SDL_Event Program::event;
bool Program::quit = false;
TTF_Font * Program::font;
int Program::framesCounter = 0;

bool Program::Init()
{
	int error = false;
	if (SDL_Init(Config::SDL_INIT_FLAGS) < 0)
	{
		printf("SDL initialization error: %s\n", SDL_GetError());
		error = true;
	}
	if (TTF_Init() == -1)
	{
		printf("SDL_TTF initialization error: %s\n", TTF_GetError());
		error = true;
	}
	if (!(IMG_Init(Config::IMG_INIT_FLAGS) & Config::IMG_INIT_FLAGS))
	{
		printf("SDL_IMG initialization error %s\n", SDL_GetError());
		error = true;
	}
	if (!(window = SDL_CreateWindow(Config::WINDOW_TITLE, Config::WINDOW_POSITION, Config::WINDOW_POSITION, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT, Config::WINDOW_FLAGS)))
	{
		printf("Window initialization error: %s\n", SDL_GetError());
		error = true;
	}
	if (!(renderer = SDL_CreateRenderer(window, Config::RENDERER_DRIVER_INDEX, Config::RENDERER_FLAGS)))
	{
		printf("Renderer initialization error: %s\n", SDL_GetError());
		error = true;
	}
	if (error) return false;
	return true;


}

bool Program::LoadContent()
{
	if(!(font = TTF_OpenFont("OpenSans.ttf", 28)))
	{
		printf("Unable to load font: %s\n", TTF_GetError());
		return false;
	}
	return true;
}


void Program::Exit()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	TTF_Quit();
	IMG_Quit();

}

void Program::EmergencyExit()
{
	Exit();
	printf("One or more errors occurred. Press any key to close the game.");
	_getch();
	exit(0);
}

void Program::HandleEvent()
{
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT) quit = true;
		else if (event.type == SDL_KEYDOWN)
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				quit = true;
				break;
			default:break;
			}
	}
}

void Program::HandleAction()
{
}

void Program::ClearRenderer()
{
	SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderClear(renderer);
}
