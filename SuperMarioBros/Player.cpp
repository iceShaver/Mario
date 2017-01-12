#include "Player.h"
#include "Object.h"
#include "stdio.h"
#include "Config.h"
#include "Program.h"
#include "Timer.h"
#include "math.h"
Player::Player(int xPos, int yPos, const char* textureFileName, Movability movable, ObjectType objectType, Transparency transparency, Color transparencyColor) : Object(xPos, yPos, textureFileName, movable, objectType, transparency, transparencyColor)
{
	jump = false;
}

Player::Player(int xPos, int yPos, Color textColor, Movability movable, ObjectType objectType) : Object(xPos, yPos, textColor, movable, objectType)
{
	jump = false;
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
		case SDLK_SPACE: jump = true; break;
		default:break;
		}
	else if (event.type == SDL_KEYUP && event.key.repeat == 0)
		switch (event.key.keysym.sym)
		{
		case SDLK_UP: yV += Config::PLAYER_SPEED; break;
		case SDLK_DOWN: yV -= Config::PLAYER_SPEED; break;
		case SDLK_LEFT: xV += Config::PLAYER_SPEED; break;
		case SDLK_RIGHT: xV -= Config::PLAYER_SPEED; break;
		default:break;
		}
}

void Player::HandleJump()
{
	if (jump)
	{
		static float zeroHeight = yPos;
		yV = -Config::PLAYER_SPEED;
		if (zeroHeight - yPos > Config::JUMP_HIGHT)
		{

			yV = Config::PLAYER_SPEED*0.5;
			jump = false;
		}
	}
}


