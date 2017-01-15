#include "Player.h"
#include "Object.h"
#include "stdio.h"
#include "Config.h"
#include "Program.h"
#include "Timer.h"
#include "math.h"
#include "Texture.h"
Player::Player(int xPos, int yPos, Texture * texture, const char * name, Movability movable, ObjectType objectType, Repeatability repeatability) : Object(xPos, yPos, texture, name, movable, objectType, repeatability)
{
	printf("New player\n");

	jump = false;
	jumping = false;
	yV = Config::PLAYER_SPEED;
	curY = yPos;
	this->yPos = yPos - height;
	livesCount = Config::INITIAL_LIVES_COUNT;

}

Player::Player(int xPos, int yPos, ObjectPosition objectPosition, const char * name, Color textColor, Movability movable, ObjectType objectType) : Object(xPos, yPos, objectPosition, name, textColor, movable, objectType)
{
	printf("New player\n");

	jump = false;
	jumping = false;
	yV = Config::PLAYER_SPEED;
	livesCount = Config::INITIAL_LIVES_COUNT;
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

	if (jump)
	{
		static bool down;
		if (!jumping)
		{
			curY = GetYPos();
			yV = -Config::PLAYER_SPEED;
			down = false;

		}
		if (((curY - GetYPos() > 300) || fabs(prevYPos - GetYPos() <= 1)) && jumping)
		{
			yV = Config::PLAYER_SPEED;
			down = true;
		}
		jumping = true;

		if (/*((fabs(curY-GetYPos())<=1) && down) || */((fabs(yPos - prevYPos) <= 1) && down))
		{
			jump = jumping = false;
			down = false;
		}
	}

}

void Player::Reset()
{
	jump = false;
	jumping = false;
	yV = Config::PLAYER_SPEED;
	xV = 0;
	collider.x = xPos = Program::loadedLevel->GetStartPlayerXPos();
	collider.y = yPos = Program::loadedLevel->GetGroundLevel() - height;
	curY = yPos;
	prevXPos = xPos;
	prevYPos = yPos;
	livesCount = Config::INITIAL_LIVES_COUNT;
}

void Player::ResetNotAll()
{
	jump = false;
	jumping = false;
	yV = Config::PLAYER_SPEED;
	collider.x = xPos = Program::loadedLevel->GetStartPlayerXPos();
	collider.y = yPos = Program::loadedLevel->GetGroundLevel() - height;
	curY = yPos;
	prevXPos = xPos;
	prevYPos = yPos;
	livesCount--;
}

void Player::GrabLive()
{
	jump = false;
	jumping = false;
	yV = Config::PLAYER_SPEED;
	collider.x = xPos = Program::loadedLevel->GetStartPlayerXPos();
	collider.y = yPos = Program::loadedLevel->GetGroundLevel() - height;
	curY = yPos;
	prevXPos = xPos;
	prevYPos = yPos;
	livesCount--;
}

int Player::GetLivesCount()
{
	return livesCount;
}


