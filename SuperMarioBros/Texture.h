#pragma once
#include <SDL.h>
#include "Config.h"

class Texture
{
public:
	struct Color
	{
		Uint8 R;
		Uint8 G;
		Uint8 B;
	};
	enum Transparency
	{
		Transparent = true,
		NonTransparent = false
	};
	Texture();
	Texture(const char * path, const char * name = "", Transparency transparency = Transparent, Color transparencyColor = {0,0,0});
	~Texture();
	bool LoadFromFile(const char * path);
	bool LoadFromRenderedText(const char * text, SDL_Color textColor);
	void Free();
	void SetColor(Uint8 red, Uint8 green, Uint8 blue);
	void SetBlendMode(SDL_BlendMode blending);
	void SetAlpha(Uint8 alpha);
	//void Render(int x, int y, SDL_Rect * clip = nullptr, double angle = 0.0, SDL_Point * center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
	const char * GetName();
	int GetWidth() const;
	int GetHeight() const;
	SDL_Texture * GetTexture() const;
private:
	char name[Config::OBJECT_NAME_LENGTH];
	Transparency transparency;
	SDL_Texture * texture;
	int width;
	int height;
	Color transparencyColor;
};

