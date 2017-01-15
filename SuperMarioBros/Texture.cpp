#include "Texture.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include "Program.h"
#include <string.h>

Texture::Texture()
{
	printf("New texture\n");
	strcpy_s(this->name, Config::OBJECT_NAME_LENGTH, "");
	texture = nullptr;
	width = 0;
	height = 0;
	transparency = NonTransparent;
	transparencyColor = { 0,0,0 };
}

Texture::Texture(const char* path, const char * name, Transparency transparency, Color transparencyColor)
{
	strcpy_s(this->name, Config::OBJECT_NAME_LENGTH, name);
	texture = nullptr;
	width = 0;
	height = 0;
	this->transparency = transparency;
	this->transparencyColor = transparencyColor;
	LoadFromFile(path);

}


Texture::~Texture()
{
	Free();
}

bool Texture::LoadFromFile(const char* path)
{
	Free();
	SDL_Surface * tmpSurface = IMG_Load(path);
	if(!tmpSurface)
	{
		SDL_FreeSurface(tmpSurface);
		printf("Unable to load image %s Error: %s\n", path, IMG_GetError());
		return false;
	}
	if (transparency)
		SDL_SetColorKey(tmpSurface, SDL_TRUE, SDL_MapRGB(tmpSurface->format, transparencyColor.R, transparencyColor.G, transparencyColor.B));
	if(!(texture = SDL_CreateTextureFromSurface(Program::renderer, tmpSurface)))
	{
		SDL_FreeSurface(tmpSurface);
		printf("Unable to create texture from surface %s Error: %s\n", path, SDL_GetError());
		return false;
	}
	width = tmpSurface->w;
	height = tmpSurface->h;
	printf("Texture %s loaded\n", path);
	SDL_FreeSurface(tmpSurface);
	return true;

}

bool Texture::LoadFromRenderedText(const char* text, SDL_Color textColor)
{
	Free();
	SDL_Surface * tmpSurface = TTF_RenderText_Shaded(Program::font, text, textColor, {0xff, 0xff, 0xff});
	if(!tmpSurface)
	{
		SDL_FreeSurface(tmpSurface);
		printf("Unable to create surface from rendered text Error: %s\n", TTF_GetError());
		return false;
	}
	if(!(texture = SDL_CreateTextureFromSurface(Program::renderer, tmpSurface)))
	{
		SDL_FreeSurface(tmpSurface);
		printf("Unable to create texture from surface Error: %s\n", SDL_GetError());
		return false;
	}
	width = tmpSurface->w;
	height = tmpSurface->h;
	SDL_FreeSurface(tmpSurface);
	return true;
}

void Texture::Free()
{
	if(texture)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
		width = 0;
		height = 0;
	}
}

void Texture::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(texture, red, green, blue);
}

void Texture::SetBlendMode(SDL_BlendMode blending)
{
	SDL_SetTextureBlendMode(texture, blending);
}

void Texture::SetAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(texture, alpha);
}

const char* Texture::GetName()
{
	return name;
}

//void Texture::Render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) const
//{
//	SDL_Rect renderRect = { x, y, width, height };
//	if(clip)
//	{
//		renderRect.w = clip->w;
//		renderRect.h = clip->h;
//	}
//	SDL_RenderCopyEx(Program::renderer, texture, clip, &renderRect, angle, center, flip);
//}

int Texture::GetWidth() const
{
	return width;
}

int Texture::GetHeight() const
{
	return height;
}

SDL_Texture* Texture::GetTexture() const
{
	return texture;
}
