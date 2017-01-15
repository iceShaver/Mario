#include "Player.h"
#include "Object.h"
#include "stdio.h"
#include "Config.h"
#include "Program.h"
#include "Timer.h"
#include "math.h"
#include "Texture.h"
#include <vector>
Player::Player(int xPos, int yPos, Texture * texture, const char * name, Movability movable, ObjectType objectType, Repeatability repeatability) : Object(xPos, yPos, texture, name, movable, objectType, repeatability)
{
	printf("New player\n");

	jump = false;
	jumping = false;
	yV = Config::PLAYER_SPEED;
	curY = yPos;

}

Player::Player(int xPos, int yPos, ObjectPosition objectPosition, const char * name, Color textColor, Movability movable, ObjectType objectType) : Object(xPos, yPos, objectPosition, name, textColor, movable, objectType)
{
	printf("New player\n");

	jump = false;
	jumping = false;
	yV = Config::PLAYER_SPEED;

	curY = yPos;

}

Player::~Player()
{
}





void Player::HandleEvent(SDL_Event & event)
{
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
		switch (event.key.keysym.sym)
		{
			//case SDLK_UP: yV -= Config::PLAYER_SPEED; break;
			//case SDLK_DOWN: yV += Config::PLAYER_SPEED; break;
		case SDLK_LEFT: xV -= Config::PLAYER_SPEED; flip = SDL_FLIP_HORIZONTAL; break;
		case SDLK_RIGHT: xV += Config::PLAYER_SPEED; flip = SDL_FLIP_NONE; break;
		case SDLK_UP: jump = true;
		default:break;
		}
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
	//Funkcja zmieniaj�ca si� w czasie (zmieniam yV w czasie)
	//Przycisk jest triggerem, dzia�a je�li nie skacze
	if (jump)
	{
		static bool down;
		if (!jumping)
		{
			curY = GetYPos(); 
			yV = -Config::PLAYER_SPEED;
			down = false;

		}
		Program::player->SetXY(GetXPos(), GetYPos() - 5.00);
		Program::player->SetXY(GetXPos(), GetYPos() + 5.0);
		if (((curY - GetYPos() > 300) || fabs(prevYPos-GetYPos() <= 1)) && jumping)
		{
			yV = Config::PLAYER_SPEED;
			down = true;
		}
		jumping = true;

		if(((fabs(curY-GetYPos())<=1) && down) || ((fabs(yPos-prevYPos) <=1) && down))
		{
			jump = jumping = false;
			down = false;
		}
	}






	/*	static float zeroHeight = yPos;
			yV = -Config::PLAYER_SPEED;
		if (zeroHeight - yPos > Config::JUMP_HIGHT)
		{

			yV = Config::PLAYER_SPEED*0.5;
			jump = false;
		}*/

		//}
		//if (jumpTimer.GetTime() >= 1000 && jumping)
		//{
		//	jumpTimer.Stop();
		//	yV = Config::PLAYER_SPEED;
		//	jump = false;
		//	//jumping = true;
		//	Player::SetXY(GetXPos(), GetYPos() + 1);
		//	if (Program::objects.ForEach(&Object::CheckCollisionWithPlayer))
		//	{
		//		Player::SetXY(GetXPos(), GetYPos() - 1.1);
		//		jumping = false;
		//		jump = false;
		//	}
		//}

}


