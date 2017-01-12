#include "Object.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include "Program.h"
#include <string.h>

Object::Object(int xPos, int yPos, const char* textureFileName, Movability movable, ObjectType objectType, Transparency transparency, Color transparencyColor)
{
	xV = 0;
	yV = 0;
	width = 0;
	height = 0;
	texture = nullptr;
	this->xPos = xPos;
	this->yPos = yPos;
	collider.x = xPos;
	collider.y = yPos;
	strcpy_s(this->texturePath, Config::TEXTURE_FILE_NAME_LENGTH, textureFileName);
	this->movable = movable;
	this->objectType = objectType;
	this->transparency = transparency;
	this->transparencyColor = transparencyColor;
	flip = SDL_FLIP_NONE;
}

Object::Object(int xPos, int yPos, Color textColor, Movability movable, ObjectType objectType)
{
	xV = 0;
	yV = 0;
	width = 0;
	height = 0;
	texture = nullptr;
	this->xPos = xPos;
	this->yPos = yPos;
	collider.x = xPos;
	collider.y = yPos;
	//strcpy_s(this->texturePath, Config::TEXTURE_FILE_NAME_LENGTH, nullptr);
	this->movable = movable;
	this->objectType = objectType;
	transparency = NonTransparent;
	transparencyColor = { 0,0,0 };
	this->textColor = textColor;
	flip = SDL_FLIP_NONE;

}

Object::~Object()
{
	dump();
}


bool Object::GetTextureFromFile()
{
	dump();
	SDL_Texture * newTexture = nullptr;
	SDL_Surface * tmpSurface = IMG_Load(texturePath);
	if (!tmpSurface)
	{
		printf("Unable to load image %s. Error: %s\n", texturePath, IMG_GetError());
		return false;
	}
	if (transparency)
		SDL_SetColorKey(tmpSurface, SDL_TRUE, SDL_MapRGB(tmpSurface->format, transparencyColor.R, transparencyColor.G, transparencyColor.B));
	if (!(newTexture = SDL_CreateTextureFromSurface(Program::renderer, tmpSurface)))
	{
		printf("Unable to create texture from image %s. Error: %s\n", texturePath, SDL_GetError());
		return false;
	}
	collider.w = width = tmpSurface->w;
	collider.h = height = tmpSurface->h;
	SDL_FreeSurface(tmpSurface);
	texture = newTexture;
	printf("Texture %s loaded\n", texturePath);
	return true;
}

void Object::dump()
{
	if (texture)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;

	}
	//width = 0;
	//height = 0;
	////strcpy_s(name, Config::OBJECT_NAME_LENGTH, nullptr);
	////collider = false;
	//movable = false;
}

bool Object::GetTextureFromText(const char* text, SDL_Color textColor)
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

bool Object::CheckCollisionWithPlayer()
{
	if (objectType) {
		SDL_Rect player = Program::player->collider;
		SDL_Rect object = collider;
		int pLeft, pRight, pTop, pBottom,
			oLeft, oRight, oTop, oBottom;
		pLeft = player.x;
		pRight = player.x + player.w;
		pTop = player.y;
		pBottom = player.y + player.h;

		oLeft = object.x;
		oRight = object.x + object.w;
		oTop = object.y;
		oBottom = object.y + object.h;

		if (pBottom <= oTop) return false;
		if (pTop >= oBottom) return false;
		if (pRight <= oLeft) return false;
		if (pLeft >= oRight) return false;
		return true;
	}
	return false;
}

int Object::GetXPos()
{
	return xPos;
}

int Object::GetYPos()
{
	return yPos;
}

int Object::GetWidth()
{
	return width;
}

int Object::GetHeight()
{
	return  height;
}

bool Object::Render(int camX, int camY,SDL_Rect* clip, double angle, SDL_Point* center) const
{
	SDL_Rect renderedRect = { xPos-Program::camera.x, yPos-Program::camera.y, width, height };

	if (clip)
	{
		renderedRect.w = clip->w;
		renderedRect.h = clip->h;
	}
	SDL_RenderCopyEx(Program::renderer, texture, clip, &renderedRect, angle, center, this->flip);
	return true;
}

bool Object::CheckCollision()
{
	return false;
}


void Object::HandleEvent(SDL_Event & event)
{



}

void Object::Move()
{
	if (movable && (xV || yV)) {
		float xOffset = xV * Program::GetDeltaTime();
		float yOffset = yV * Program::GetDeltaTime();
		xPos += xOffset;
		collider.x = xPos;
		if (xPos<0 || xPos + width>Config::LEVEL_WIDTH || Program::objects.ForEach(&Object::CheckCollisionWithPlayer))
		{
			xPos -= xOffset;
			collider.x = xPos;
			while (true)
			{
				if (xOffset > 0)xPos++;
				else xPos--;
				collider.x = xPos;
				if (xPos<0 || xPos + width>Config::LEVEL_WIDTH || Program::objects.ForEach(&Object::CheckCollisionWithPlayer))
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

		if (yPos<0 || yPos + height>Config::LEVEL_HEIGHT || Program::objects.ForEach(&Object::CheckCollisionWithPlayer))
		{
			yPos -= yOffset;
			collider.y = yPos;
			while (true)
			{
				if (yOffset > 0)yPos++;
				else yPos--;
				collider.y = yPos;
				if (yPos<0 || yPos + height>Config::LEVEL_HEIGHT || Program::objects.ForEach(&Object::CheckCollisionWithPlayer))
				{
					if (yOffset > 0)yPos--;
					else yPos++;
					collider.y = yPos;
					break;
				}
			}
		}



	}


}
