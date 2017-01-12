#pragma once
#include "Config.h"
class Object
{
protected:
	struct Color
	{
		Uint8 R;
		Uint8 G;
		Uint8 B;
	};
public:
	enum ObjectType
	{
		Solid = true,
		Virtual = false
	};
	enum Transparency
	{
		Transparent = true,
		NonTransparent = false
	};
	enum Movability
	{
		Movable = true,
		NonMovable = false
	};
	//template <class Object> friend class List;
public:

	Object(int xPos, int yPos, const char * textureFileName, Movability movable = NonMovable, ObjectType objectType = Solid, Transparency transparency = Transparent, Color transparencyColor = { 0,0,0 });
	Object(int xPos, int yPos, Color textColor = { 0,0,0 }, Movability movable = NonMovable, ObjectType objectType = Solid);
	virtual ~Object();
	virtual void HandleEvent(SDL_Event & event);
	virtual void Move();
	bool GetTextureFromFile();
	bool GetTextureFromText(const char * text, SDL_Color color);
	bool CheckCollisionWithPlayer();
	int GetXPos();
	int GetYPos();
	int GetWidth();
	int GetHeight();
	bool Render(int camX = 0, int camY = 0,SDL_Rect * clip = nullptr, double angle = 0.0, SDL_Point * center = nullptr) const;

protected:

	int xV, yV;
	char texturePath[Config::TEXTURE_FILE_NAME_LENGTH];
	float xPos;
	float yPos;
	int width;
	int height;
	ObjectType objectType;
	Movability movable;
	SDL_Texture * texture;
	SDL_RendererFlip flip;
	SDL_Rect collider;
	Color textColor;
	Transparency transparency;
	Color transparencyColor;
	void dump();
	bool CheckCollision();

};


