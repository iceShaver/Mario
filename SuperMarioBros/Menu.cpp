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
			Program::EndGame();
			Program::loadedLevel = Program::levels.GetFirst();
			Program::StartTheGame(); break;
		case SDLK_RETURN:
			Program::LoadNextLevel(); 
			break;
		default:break;
		}
	}
}

void Menu::DisplayMenu()
{
	switch (menuBehaviour)
	{
	case Win:
		Program::DisplayText("Wygrałeś", (Config::SCREEN_WIDTH / 2) - 50, (Config::SCREEN_HEIGHT / 4), { 0x44, 0xff, 0x44 }, Program::gameFont);
		Program::DisplayText("ENTER - następny etap", (Config::SCREEN_WIDTH / 2) - 50, (Config::SCREEN_HEIGHT / 2)-40, { 0x44, 0xff, 0x44 }, Program::gameFont);
		break;
	case Lose:
		Program::DisplayText("Przegrałeś", (Config::SCREEN_WIDTH / 2) - 50, (Config::SCREEN_HEIGHT / 4), { 0x44, 0xff, 0x44 }, Program::gameFont);
		Program::levels.ForEach(&Level::Uncomplete);
		break;
	case None:
		break;
	default:
		break;

	}
	Program::DisplayText("n - nowa gra", (Config::SCREEN_WIDTH / 2) - 100, (Config::SCREEN_HEIGHT / 2), Config::MENU_FONT_COLOR, Program::gameFont);
	Program::DisplayText("ESC - wyjście", (Config::SCREEN_WIDTH / 2) - 100, (Config::SCREEN_HEIGHT / 2)+40, Config::MENU_FONT_COLOR, Program::gameFont);

		

}




