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
TTF_Font * Program::standardFont;
TTF_Font * Program::gameFont;
List<Object> Program::objects;
List<Level> Program::levels;
Player * Program::player;
Object * Program::background;
Object * Program::ground;
Timer Program::deltaTimer;
Level * Program::loadedLevel;
int Program::remainingTime;
bool Program::gameStarted;
Menu * Program::menu;
//Texture * Program::backgroundTexture;
//Texture * Program::groundTexture;
//Texture * Program::wallTexture;
//Texture * Program::playerTexture;
List<Texture> Program::textures;
//SDL_Rect Program::camera;
bool Program::Init()
{
	//timer.Start();
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
	textures.Add(new Texture("textures/background.png", "background"));
	textures.Add(new Texture("textures/marioTexture.png", "player", Texture::Transparent, { 0xff,0xff,0xff }));
	textures.Add(new Texture("textures/ground.png", "ground", Texture::Transparent, { 0xff, 0xff, 0xff }));
	textures.Add(new Texture("textures/wall.png", "wall"));
	background = new Object(0, 0, textures.Get("background"), "background", Object::NonMovable, Object::Virtual, Object::Repeatable);
	objects.Add(background);
	levels.Add(new Level("levels/level1.lvl"));
	loadedLevel = levels.Get("Default Level");
	player = new Player(loadedLevel->GetStartPlayerXPos(), loadedLevel->GetGroundLevel(), textures.Get("player"), "player", Object::Movable, Object::Virtual, Object::NonRepeatable);
	ground = new Object(0, 556, textures.Get("ground"), "ground", Object::NonMovable, Object::Solid, Object::Repeatable);
	Object * wall = new Object(800, loadedLevel->GetHeight() - 300, textures.Get("wall"));
	objects.Add(ground);
	objects.Add(player);
	objects.Add(wall);
	camera.Follow(player);
	gameStarted = false;
	menu = new Menu();
	menu->SetMenu(Menu::None);
	//SDL_RenderSetScale(renderer, 0.5, 0.5);
	if (error) return false;
	return true;


}

bool Program::LoadContent()
{
	if (!(standardFont = TTF_OpenFont(Config::STANDARD_FONT, Config::STANDARD_FONT_SIZE)))
	{
		printf("Unable to load font: %s\n", TTF_GetError());
		return false;
	}
	if (!(gameFont = TTF_OpenFont(Config::GAME_FONT, Config::GAME_FONT_SIZE)))
	{
		printf("Unable to load font: %s\n", TTF_GetError());
		return false;
	}
	/*background->GetTextureFromFile();
	player->GetTextureFromFile();
	ground->GetTextureFromFile();*/
	//objects.ForEach(&Object::GetTextureFromFile);
	return true;
}

void Program::Render()
{



	//player->Render();

	objects.ForEach(&Object::Render);
	//loadedLevel->RenderObjects();
	//player->Render();
}


void Program::Exit()
{
	//delete background;
	//delete player;
	//delete ground;
	TTF_CloseFont(standardFont);
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
		if (gameStarted)
			player->HandleEvent(event);
		menu->HandleEvent(event);

	}
}

bool Program::EndTime()
{
	if (remainingTime <= 0) return true;
	return false;
}

void Program::CountRemainingTime()
{
	remainingTime = loadedLevel->GetTime() - timer.GetTime();
}



void Program::HandleAction()
{


	player->HandleJump();
	player->Move();
	CountRemainingTime();
	if (EndTime()) {
		player->GrabLive();
		timer.Start();
		if (player->GetLivesCount() == 0) {
			gameStarted = false;
			menu->SetMenu(Menu::Lose);
			EndGame();
		}

	}
	if (player->GetXPos() >= loadedLevel->GetEndXPos())
	{
		gameStarted = false;
		menu->SetMenu(Menu::Win);
		EndGame();
	}


}

void Program::ClearRenderer()
{
	SDL_SetRenderDrawColor(renderer, 0x88, 0xaa, 0xff, 0);
	SDL_RenderClear(renderer);
}

void Program::SetDeltaTime()
{
	deltaTime = deltaTimer.GetTime() / 1000.f;
	deltaTimer.Start();
}



float Program::GetDeltaTime()
{
	return deltaTime;
}



void Program::DisplayText(const char* text, int x, int y, Texture::Color color, TTF_Font * font)
{
	SDL_Surface * tmpSurface = TTF_RenderUTF8_Blended(font, text, { color.R, color.G, color.B });
	SDL_Texture * texture;
	if (!tmpSurface)
	{
		printf("Unable to create text surface: %s\n", SDL_GetError());
	}
	if (!(texture = SDL_CreateTextureFromSurface(Program::renderer, tmpSurface)))
	{
		printf("Unable to create text texture. Error: %s\n", SDL_GetError());
	}
	int width = tmpSurface->w;
	int height = tmpSurface->h;
	SDL_FreeSurface(tmpSurface);

	SDL_Rect renderedRect = { x, y, width, height };
	SDL_RenderCopyEx(Program::renderer, texture, nullptr, &renderedRect, 0.0, nullptr, SDL_FLIP_NONE);
	SDL_DestroyTexture(texture);
}


void Program::DisplayDiagnosticInfo()
{
	char text[256];
	sprintf_s(text, 256, "AVG FPS: %.2f || CUR FPS: %.2f || Frames Count: %d || Time: %.2f || Player position: (%d,%d)", fpsGauge.GetAverageFPS(), fpsGauge.GetCurrentFPS(), fpsGauge.GetFramesCount(), (timer.GetTime() / 1000.f), player->GetXPos(), player->GetYPos());
	DisplayText(text, 0, 0);


}

void Program::DisplayInfo()
{
	char text[64];
	sprintf_s(text, 64, "Pozostały czas: %d", remainingTime);
	DisplayText(text, 0, 20, { 0xda, 0xa5, 0x20 }, gameFont);
	sprintf_s(text, 64, "Ukończono: %.1f\%%", 100 * (player->GetXPos() / static_cast<float>(loadedLevel->GetEndXPos())));
	DisplayText(text, 0, 40, { 0xda, 0xa5, 0x20 }, gameFont);
	sprintf_s(text, 64, "Liczba żyć: %d", player->GetLivesCount());
	DisplayText(text, 0, 60, { 0xda, 0xa5, 0x20 }, gameFont);

}



void Program::DisplayMenu()
{
	menu->DisplayMenu();
	//gameStarted = true;
}

void Program::StartTheGame()
{
	player->Reset();
	gameStarted = true;
	timer.Start();
}

void Program::EndGame()
{
	player->Reset();
	timer.Stop();
}


bool Program::IsGameStarted()
{
	return gameStarted;
}
