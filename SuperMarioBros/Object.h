#pragma once
#include "Config.h"
class Object
{
	//template <class Object> friend class List;
public:
	Object();
	Object(const char * name);
	Object(const char * name, int xPos, int Ypos);
	~Object();
	virtual bool Init();
	virtual bool LoadContent();
	virtual bool Exit();
	virtual bool Render();
	virtual void HandleEvent(SDL_Event & event);
	virtual void Move();
	bool CreateText();
protected:
	int xV, yV;
	int xPos;
	int yPos;
	int width;
	int height;
	//bool collider;
	bool movable;
	SDL_Texture * texture;
	SDL_Rect collider;
	bool getTextureFromFile(const char * path);
	bool getTextureFromFile(const char * path, Uint8 R, Uint8 G, Uint8 B);
	void dump();
	bool getTextureFromText(const char * text, SDL_Color color);
	bool render(int x, int y, SDL_Rect * clip = nullptr, double angle = 0.0, SDL_Point * center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
	bool checkCollision();

};


