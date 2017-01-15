#include "Player.h"
#include "Object.h"
#include "stdio.h"
#include "Config.h"
#include "Program.h"
#include "Timer.h"
#include "math.h"
#include "Texture.h"
#include <vector>
Player::Player(int xPos, int yPos, Texture * texture,const char * name, Movability movable, ObjectType objectType,Repeatability repeatability) : Object(xPos, yPos, texture,name, movable, objectType, repeatability)
{
	printf("New player\n");

	jump = false;
	jumping = false;
}

Player::Player(int xPos, int yPos, ObjectPosition objectPosition,const char * name ,Color textColor, Movability movable, ObjectType objectType) : Object(xPos, yPos,objectPosition, name, textColor, movable, objectType)
{
	printf("New player\n");

	jump = false;
	jumping = false;
}

Player::~Player()
{
}





void Player::HandleEvent(SDL_Event & event)
{
	yV = Config::PLAYER_SPEED*0.5;
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
		switch (event.key.keysym.sym)
		{
			//case SDLK_UP: yV -= Config::PLAYER_SPEED; break;
			//case SDLK_DOWN: yV += Config::PLAYER_SPEED; break;
		case SDLK_LEFT: xV -= Config::PLAYER_SPEED; flip = SDL_FLIP_HORIZONTAL; break;
		case SDLK_RIGHT: xV += Config::PLAYER_SPEED; flip = SDL_FLIP_NONE; break;
		case SDLK_UP: jump = true; break;
		default:break;
		}
	else if (event.type == SDL_KEYUP && event.key.repeat == 0)
		switch (event.key.keysym.sym)
		{
		//case SDLK_UP: yV += Config::PLAYER_SPEED; break;
		//case SDLK_DOWN: yV -= Config::PLAYER_SPEED; break;
		case SDLK_LEFT: xV += Config::PLAYER_SPEED; break;
		case SDLK_RIGHT: xV -= Config::PLAYER_SPEED; break;
		default:break;
		}
}

void Player::HandleJump()
{
	static int jumpHeight = 0;
	//Funkcja zmieniaj¹ca siê w czasie (zmieniam yV w czasie)
	//Przycisk jest triggerem, dzia³a jeœli nie skacze

	if (jump)
	{
		jump = false;
		jumpTimer.Start();
		yV = -Config::PLAYER_SPEED;
		if(jumpTimer.GetTime() >= 1000)
		{
			yV = Config::PLAYER_SPEED;
			jump = false;
		}









	/*	static float zeroHeight = yPos;
			yV = -Config::PLAYER_SPEED;
		if (zeroHeight - yPos > Config::JUMP_HIGHT)
		{

			yV = Config::PLAYER_SPEED*0.5;
			jump = false;
		}*/

	}

}


