#include "Object.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include "Program.h"
#include <string.h>
#include "Camera.h"
Camera Program::camera;
//Object::Object(int xPos, int yPos, const char* textureFileName, Movability movable, ObjectType objectType, Repeatability repeatability, Transparency transparency, Color transparencyColor)
//{
//	xV = 0;
//	yV = 0;
//	width = 0;
//	height = 0;
//	texture = nullptr;
//	this->xPos = xPos;
//	this->yPos = yPos;
//	collider.x = xPos;
//	collider.y = yPos;
//	strcpy_s(this->texturePath, Config::TEXTURE_FILE_NAME_LENGTH, textureFileName);
//	this->movable = movable;
//	this->objectType = objectType;
//	this->transparency = transparency;
//	this->transparencyColor = transparencyColor;
//	flip = SDL_FLIP_NONE;
//	clip = nullptr;
//	angle = 0.0;
//	center = nullptr;
//	repeatable = repeatability;
//
//}

Object::Object(int xPos, int yPos, Texture * texture, const char * name, Movability movable, ObjectType objectType, Repeatability repeatability, ObjectPosition objectPosition)
{
	printf("New object\n");

	xV = 0;
	yV = 0;
	collider.w = width = texture->GetWidth();
	collider.h = height = texture->GetHeight();
	//texture = nullptr;
	this->objectPosition = objectPosition;
	this->xPos = xPos;
	this->yPos = yPos;
	collider.x = xPos;
	collider.y = yPos;
	this->texture = texture->GetTexture();//Here is the error, texture is nullptr, WHY???
	this->movable = movable;
	this->objectType = objectType;
	flip = SDL_FLIP_NONE;
	clip = nullptr;
	angle = 0.0;
	center = nullptr;
	repeatable = repeatability;
	strcpy_s(this->name, Config::OBJECT_NAME_LENGTH, name);
	prevXPos = xPos;
	prevYPos = yPos;
}


Object::Object(int xPos, int yPos, ObjectPosition objectPosition, const char * name, Color textColor, Movability movable, ObjectType objectType)
{
	printf("New object\n");
	this->objectPosition = objectPosition;
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
	//transparency = NonTransparent;
	//transparencyColor = { 0,0,0 };
	this->textColor = textColor;
	flip = SDL_FLIP_NONE;
	clip = nullptr;
	angle = 0.0;
	center = nullptr;
	repeatable = NonRepeatable;
	strcpy_s(this->name, Config::OBJECT_NAME_LENGTH, name);
	prevXPos = xPos;
	prevYPos = yPos;


}

Object::~Object()
{
	dump();
}


//bool Object::GetTextureFromFile()
//{
//	dump();
//	SDL_Texture * newTexture = nullptr;
//	SDL_Surface * tmpSurface = IMG_Load(texturePath);
//	if (!tmpSurface)
//	{
//		printf("Unable to load image %s. Error: %s\n", texturePath, IMG_GetError());
//		return false;
//	}
//	if (transparency)
//		SDL_SetColorKey(tmpSurface, SDL_TRUE, SDL_MapRGB(tmpSurface->format, transparencyColor.R, transparencyColor.G, transparencyColor.B));
//	if (!(newTexture = SDL_CreateTextureFromSurface(Program::renderer, tmpSurface)))
//	{
//		printf("Unable to create texture from image %s. Error: %s\n", texturePath, SDL_GetError());
//		return false;
//	}
//	collider.w = width = tmpSurface->w;
//	collider.h = height = tmpSurface->h;
//	SDL_FreeSurface(tmpSurface);
//	texture = newTexture;
//	printf("Texture %s loaded\n", texturePath);
//	return false;
//}

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
	SDL_Surface * tmpSurface = TTF_RenderText_Blended(Program::standardFont, text, textColor);
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

const char* Object::GetName()
{
	return name;
}

bool Object::Render()
{
	SDL_Rect renderedRect;
	if (objectPosition == Relative)
		renderedRect = { static_cast<int>(xPos) - Program::camera.GetXPos(), static_cast<int>(yPos) - Program::camera.GetYPos(), width, height };
	else
		renderedRect = { static_cast<int>(xPos), static_cast<int>(yPos), width, height };

	if (clip)
	{
		renderedRect.w = clip->w;
		renderedRect.h = clip->h;
	}
	if (repeatable)
	{
		SDL_RenderCopyEx(Program::renderer, texture, clip, &renderedRect, angle, center, flip);

		while (renderedRect.x + renderedRect.w < Program::camera.GetXPos() + Program::camera.GetWidth())
		{
			renderedRect.x += renderedRect.w;
			collider.w += width;
			SDL_RenderCopyEx(Program::renderer, texture, clip, &renderedRect, angle, center, flip);
		}
	}
	else
		SDL_RenderCopyEx(Program::renderer, texture, clip, &renderedRect, angle, center, flip);
	return false;
}

void Object::SetXY(int x, int y)
{
	xPos = x;
	yPos = y;
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
	prevXPos = xPos;
	prevYPos = yPos;
	if (movable && (xV || yV)) {

		float xOffset = xV * Program::GetDeltaTime();
		float yOffset = yV * Program::GetDeltaTime();
		xPos += xOffset;
		collider.x = xPos;
		if (xPos<0 || xPos + width>Program::loadedLevel->GetWidth() || Program::objects.ForEach(&Object::CheckCollisionWithPlayer))
		{
			xPos -= xOffset;
			collider.x = xPos;
			while (true)
			{
				if (xOffset > 0)xPos++;
				else xPos--;
				collider.x = xPos;
				if (xPos<0 || xPos + width>Program::loadedLevel->GetWidth() || Program::objects.ForEach(&Object::CheckCollisionWithPlayer))
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

		if (yPos<0 || yPos + height>Program::loadedLevel->GetHeight() || Program::objects.ForEach(&Object::CheckCollisionWithPlayer))
		{
			yPos -= yOffset;
			collider.y = yPos;
			while (true)
			{
				if (yOffset > 0)yPos++;
				else yPos--;
				collider.y = yPos;
				if (yPos<0 || yPos + height>Program::loadedLevel->GetHeight() || Program::objects.ForEach(&Object::CheckCollisionWithPlayer))
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
