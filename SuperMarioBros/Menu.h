#pragma once
#include <SDL.h>
class Menu
{
public:
	enum MenuBehaviour
	{
		Win, Lose, None
	};
	Menu();
	~Menu();
	void SetMenu(MenuBehaviour menuBehaviour);
	void HandleEvent(SDL_Event & event);
	void DisplayMenu();

private:
	MenuBehaviour menuBehaviour;
};

