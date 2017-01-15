#include "Menu.h"
#include "Config.h"
#include <SDL.h>
#include "Program.h"

Menu::Menu()
{
	menuBehaviour = None;
}


Menu::~Menu()
{
}

void Menu::SetMenu(MenuBehaviour menuBehaviour)
{
	this->menuBehaviour = menuBehaviour;
}

void Menu::HandleEvent(SDL_Event & event)
{
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
		switch (event.key.keysym.sym)
		{
		case SDLK_n: 
			Program::StartTheGame(); break;
		default:break;
		}
	}
}

void Menu::DisplayMenu()
{
	switch (menuBehaviour)
	{
	case Win:
		Program::DisplayText("Wygrałeś", (Config::SCREEN_WIDTH / 2) - 50, (Config::SCREEN_HEIGHT / 2) - 50, { 0x44, 0xff, 0x44 }, Program::gameFont);
		break;
	case Lose:
		Program::DisplayText("Przegrałeś", (Config::SCREEN_WIDTH / 2) - 50, (Config::SCREEN_HEIGHT / 2) - 50, { 0x44, 0xff, 0x44 }, Program::gameFont);
		break;
	case None:
		break;
	default:
		break;

	}

		

}




