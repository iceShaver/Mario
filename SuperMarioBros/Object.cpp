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
	collider = false;
	movable = false;
	xPos = 0;
	yPos = 0;
}

Object::Object(const char * name)
{
	//dump();
	SDL_DestroyTexture(texture);
	texture = nullptr;
	width = 0;
	height = 0;
	//strcpy_s(this->name, Config::OBJECT_NAME_LENGTH, name);
	collider = false;
	movable = false;
	xPos = 0;
	yPos = 0;
}

Object::Object(const char * name, int xPos, int yPos)
{
	//dump();
	texture = nullptr;
	width = 0;
	height = 0;
	//strcpy_s(this->name, Config::OBJECT_NAME_LENGTH, name);
	collider = false;
	movable = false;
	this->xPos = xPos;
	this->yPos = yPos;
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
	if(!tmpSurface)
	{
		printf("Unable to load image %s. Error: %s\n", path, IMG_GetError());
		return false;
	}
	SDL_SetColorKey(tmpSurface, SDL_TRUE, SDL_MapRGB(tmpSurface->format, R, G, B));
	if(!(newTexture = SDL_CreateTextureFromSurface(Program::renderer, tmpSurface)))
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
	if(texture)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;

	}
	width = 0;
	height = 0;
	//strcpy_s(name, Config::OBJECT_NAME_LENGTH, nullptr);
	collider = false;
	movable = false;
}

bool Object::getTextureFromText(const char* text, SDL_Color textColor)
{
	dump();
	SDL_Surface * tmpSurface = TTF_RenderText_Blended(Program::font, text, textColor);
	if(!tmpSurface)
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

bool Object::HandleEvent()
{
	return false;
}

bool Object::HandleAction()
{
	return false;
}
