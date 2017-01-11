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
	bool Render();
	virtual bool HandleEvent();
	virtual bool HandleAction();
	bool CreateText();
protected:
	int xPos;
	int yPos;
	int width;
	int height;
	char name[Config::OBJECT_NAME_LENGTH];
	bool collider;
	bool movable;
	SDL_Texture * texture;
	bool getTextureFromFile(const char * path);
	bool getTextureFromFile(const char * path, Uint8 R, Uint8 G, Uint8 B);
	void dump();
	bool getTextureFromText(const char * text, SDL_Color color);



};


