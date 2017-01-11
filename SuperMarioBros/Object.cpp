#include "Object.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include "Program.h"
Object::Object()
{
	//dump();
	texture = nullptr;
	width = 0;
	height = 0;
	//	strcpy_s(this->name, Config::OBJECT_NAME_LENGTH, nullptr);
	//collider = false;
	movable = false;
	xPos = 0;
	yPos = 0;
	xV = 0;
	yV = 0;
}

Object::Object(const char * name)
{
	//dump();
	SDL_DestroyTexture(texture);
	texture = nullptr;
	width = 0;
	height = 0;
	//strcpy_s(this->name, Config::OBJECT_NAME_LENGTH, name);
	//collider = false;
	movable = false;
	xPos = 0;
	yPos = 0;
	xV = 0;
	yV = 0;
}

Object::Object(const char * name, int xPos, int yPos)
{
	//dump();
	texture = nullptr;
	width = 0;
	height = 0;
	//strcpy_s(this->name, Config::OBJECT_NAME_LENGTH, name);
	//collider = false;
	movable = false;
	this->xPos = xPos;
	this->yPos = yPos;
	xV = 0;
	yV = 0;
}

Object::~Object()
{
	dump();
}

bool Object::Init()
{
	return false;
}

bool Object::LoadContent()
{

	return false;
}

bool Object::Exit()
{
	return false;
}

bool Object::Render()
{
	return false;
}


bool Object::getTextureFromFile(const char* path)
{
	dump();
	SDL_Texture * newTexture = nullptr;
	SDL_Surface * tmpSurface = IMG_Load(path);
	if (!tmpSurface)
	{
		printf("Unable to load image %s. Error: %s\n", path, IMG_GetError());
		return false;
	}
	if (!(newTexture = SDL_CreateTextureFromSurface(Program::renderer, tmpSurface)))
	{
		printf("Unable to create texture from image %s. Error: %s\n", path, SDL_GetError());
		return false;
	}
	width = tmpSurface->w;
	height = tmpSurface->h;
	SDL_FreeSurface(tmpSurface);
	texture = newTexture;
	return true;
}

bool Object::getTextureFromFile(const char* path, Uint8 R, Uint8 G, Uint8 B)
{
	dump();
	SDL_Texture * newTexture = nullptr;
	SDL_Surface * tmpSurface = IMG_Load(path);
	if (!tmpSurface)
	{
		printf("Unable to load image %s. Error: %s\n", path, IMG_GetError());
		return false;
	}
	SDL_SetColorKey(tmpSurface, SDL_TRUE, SDL_MapRGB(tmpSurface->format, R, G, B));
	if (!(newTexture = SDL_CreateTextureFromSurface(Program::renderer, tmpSurface)))
	{
		printf("Unable to create texture from image %s. Error: %s\n", path, SDL_GetError());
		return false;
	}
	width = tmpSurface->w;
	height = tmpSurface->h;
	SDL_FreeSurface(tmpSurface);
	texture = newTexture;
	return true;
}

void Object::dump()
{
	if (texture)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;

	}
	width = 0;
	height = 0;
	//strcpy_s(name, Config::OBJECT_NAME_LENGTH, nullptr);
	//collider = false;
	movable = false;
}

bool Object::getTextureFromText(const char* text, SDL_Color textColor)
{
	dump();
	SDL_Surface * tmpSurface = TTF_RenderText_Blended(Program::font, text, textColor);
	if (!tmpSurface)
	{
		printf("Unable to create text surface: %s\n", SDL_GetError());
		return false;
	}
	if (!(texture = SDL_CreateTextureFromSurface(Program::renderer, tmpSurface)))
	{
		printf("Unable to create text texture. Error: %s\n", SDL_GetError());
		return false;
	}
	width = tmpSurface->w;
	height = tmpSurface->h;
	SDL_FreeSurface(tmpSurface);
	return true;
}

bool Object::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) const
{
	SDL_Rect renderedRect = { x, y, width, height };
	if (clip)
	{
		renderedRect.w = clip->w;
		renderedRect.h = clip->h;
	}
	SDL_RenderCopyEx(Program::renderer, texture, clip, &renderedRect, angle, center, flip);
	return true;
}

bool Object::checkCollision()
{
	return false;
}


void Object::HandleEvent(SDL_Event & event)
{
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
		switch (event.key.keysym.sym)
		{
		case SDLK_UP: yV -= Config::PLAYER_SPEED; break;
		case SDLK_DOWN: yV += Config::PLAYER_SPEED; break;
		case SDLK_LEFT: xV -= Config::PLAYER_SPEED; break;
		case SDLK_RIGHT: xV += Config::PLAYER_SPEED; break;
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

void Object::Move()
{
	float xOffset = xV ;
	float yOffset = yV ;
	xPos += xOffset;
	collider.x = xPos;
	if (xPos<0 || xPos + width>Config::LEVEL_WIDTH || checkCollision())
	{
		xPos -= xOffset;
		collider.x = xPos;
		while(true)
		{
			if (xOffset > 0)xPos++;
			else xPos--;
			collider.x = xPos;
			if(xPos<0 || xPos+width>Config::LEVEL_WIDTH || checkCollision())
			{
				if (xOffset > 0)xPos--;
				else xPos++;
				collider.x = xPos;
				break;;
			}
		}
	}

	yPos += yOffset;
	collider.y = yPos;

	if(yPos<0 || yPos+height>Config::LEVEL_HEIGHT || checkCollision())
	{
		yPos -= yOffset;
		collider.y = yPos;
		while(true)
		{
			if (yOffset > 0)yPos++;
			else yPos--;
			collider.y = yPos;
			if(yPos<0 || yPos+height>Config::LEVEL_HEIGHT || checkCollision())
			{
				if (yOffset > 0)yPos--;
				else yPos++;
				collider.y = yPos;
				break;
			}
		}
	}








}
