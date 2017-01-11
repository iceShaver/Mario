#include "Texture.h"
#include <SDL_image.h>
#include <cstdio>
#include "Program.h"


Texture::Texture()
{
	texture = nullptr;
	width = 0;
	height = 0;
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
	if(!(texture = SDL_CreateTextureFromSurface(Program::renderer, tmpSurface)))
	{
		SDL_FreeSurface(tmpSurface);
		printf("Unable to create texture from surface %s Error: %s\n", path, SDL_GetError());
		return false;
	}
	width = tmpSurface->w;
	height = tmpSurface->h;
	SDL_FreeSurface(tmpSurface);
	return true;

}

bool Texture::LoadFromRenderedText(const char* text, SDL_Color textColor)
{
	Free();
	SDL_Surface * tmpSurface = TTF_RenderText_Blended(Program::font, text, textColor);
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

void Texture::Render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) const
{
	SDL_Rect renderRect = { x, y, width, height };
	if(clip)
	{
		renderRect.w = clip->w;
		renderRect.h = clip->h;
	}
	SDL_RenderCopyEx(Program::renderer, texture, clip, &renderRect, angle, center, flip);
}

int Texture::GetWidth() const
{
	return width;
}

int Texture::GetHeight() const
{
	return height;
}
