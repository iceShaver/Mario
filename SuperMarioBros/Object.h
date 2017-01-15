#pragma once
#include "Config.h"
#include "Texture.h"

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
	enum Repeatability
	{
		Repeatable = true,
		NonRepeatable = false
	};
	
	enum Movability
	{
		Movable = true,
		NonMovable = false
	};
	enum ObjectPosition
	{
		Fixed,Relative
	};
	//template <class Object> friend class List;
public:

	/*Object(int xPos, int yPos, const char * textureFileName, Movability movable = NonMovable, ObjectType objectType = Solid, Repeatability repeatability = NonRepeatable, Transparency transparency = Transparent, Color transparencyColor = { 0,0,0 });*/
	Object(int xPos, int yPos, Texture * texture, const char * name = "", Movability movable = NonMovable, ObjectType objectType = Solid, Repeatability repeatability = NonRepeatable, ObjectPosition objectPosition = Relative);
	Object(int xPos, int yPos,  ObjectPosition objectPosition = Relative, const char * name = "", Color textColor = { 0,0,0 }, Movability movable = NonMovable, ObjectType objectType = Virtual );
	virtual ~Object();
	virtual void HandleEvent(SDL_Event & event);
	virtual void Move();
	//bool GetTextureFromFile();
	bool GetTextureFromText(const char * text, SDL_Color color);
	bool CheckCollisionWithPlayer();
	int GetXPos();
	int GetYPos();
	int GetWidth();
	int GetHeight();
	const char * GetName();
	bool Render();
	void SetXY(int x, int y);

protected:

	int xV, yV;
	char texturePath[Config::TEXTURE_FILE_NAME_LENGTH];
	float xPos;
	float yPos;
	int width;
	int height;
	char name[Config::OBJECT_NAME_LENGTH];
	ObjectType objectType;
	Movability movable;
	Repeatability repeatable;
	SDL_Texture * texture;
	SDL_RendererFlip flip;
	SDL_Rect collider;
	Color textColor;
	//Transparency transparency;
	//Color transparencyColor;
	SDL_Rect * clip;
	double angle;
	SDL_Point * center;
	ObjectPosition objectPosition;
	void dump();
	bool CheckCollision();

};


