#include "Program.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "Config.h"
#include <stdio.h>
#include "Object.h"
#include "Player.h"
#include <conio.h>
#include "List.h"
SDL_Window * Program::window;
SDL_Renderer * Program::renderer;
SDL_Event Program::event;
bool Program::quit = false;
TTF_Font * Program::font;
List<Object> Program::objects;
Player * Program::player;
Object * Program::background;
Object * Program::ground;
Timer Program::deltaTimer;
//SDL_Rect Program::camera;
bool Program::Init()
{
	timer.Start();
	fpsGauge.AverageFPSTimerStart();
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
	SDL_RenderSetLogicalSize(renderer, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
	deltaTime = 0;
	background = new Object(0, 0, "textures/background.png", Object::NonMovable, Object::Virtual, Object::Repeatable);
	player = new Player(Config::SCREEN_WIDTH/2,Config::SCREEN_HEIGHT/2, "textures/mario.png",Object::Movable , Object::Virtual, Object::NonRepeatable, Object::Transparent, {0xff, 0xff, 0xff});
	ground = new Object(0, 556, "textures/ground.png", Object::NonMovable, Object::Solid, Object::Repeatable);
	objects.Add(background);
	objects.Add(ground);
	objects.Add(player);
	camera.Follow(player);
	//SDL_RenderSetScale(renderer, 0.5, 0.5);
	if (error) return false;
	return true;


}

bool Program::LoadContent()
{
	if(!(font = TTF_OpenFont(Config::FONT, 12)))
	{
		printf("Unable to load font: %s\n", TTF_GetError());
		return false;
	}
	/*background->GetTextureFromFile();
	player->GetTextureFromFile();
	ground->GetTextureFromFile();*/
	objects.ForEach(&Object::GetTextureFromFile);
	return true;
}

void Program::Render()
{



	//player->Render();
	objects.ForEach(&Object::Render);
	//player->Render();
}


void Program::Exit()
{
	//delete background;
	//delete player;
	//delete ground;
	TTF_CloseFont(font);
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
		player->HandleEvent(event);
	}
}

void Program::HandleAction()
{
	//objects.GetLast()->Move();
	player->HandleJump();
	player->Move();
}

void Program::ClearRenderer()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
}

void Program::SetDeltaTime()
{
	deltaTime = deltaTimer.GetTime()/1000.f;
	deltaTimer.Start();
}



float Program::GetDeltaTime()
{
	return deltaTime;
}

void Program::DisplayPlayerXY()
{
	Texture xy;
	char text[20];
	sprintf_s(text, 20, "(%d, %d)", player->GetXPos(), player->GetYPos());
	xy.LoadFromRenderedText(text, { 0,0,0 });
	xy.Render(Config::SCREEN_WIDTH - xy.GetWidth(), 0);
	//xy.LoadFromRenderedText()
}
