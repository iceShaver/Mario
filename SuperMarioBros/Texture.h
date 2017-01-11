#pragma once
#include <SDL.h>
class Texture
{
public:
	Texture();
	~Texture();
	bool LoadFromFile(const char * path);
	bool LoadFromRenderedText(const char * text, SDL_Color textColor);
	void Free();
	void SetColor(Uint8 red, Uint8 green, Uint8 blue);
	void SetBlendMode(SDL_BlendMode blending);
	void SetAlpha(Uint8 alpha);
	void Render(int x, int y, SDL_Rect * clip = nullptr, double angle = 0.0, SDL_Point * center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
	int GetWidth() const;
	int GetHeight() const;
private:
	SDL_Texture * texture;
	int width;
	int height;
};

