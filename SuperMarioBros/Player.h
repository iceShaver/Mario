#pragma once
#include "Object.h"
#include "Timer.h"
#include "Texture.h"

//class Object::HandleEvent;
class Player : public Object
{
public:
	Player(int xPos, int yPos, Texture * texture,const char * name = "", Movability movable = NonMovable, ObjectType objectType = Solid, Repeatability repeatability = NonRepeatable);
	Player(int xPos, int yPos,ObjectPosition objectPosition = Relative, const char * name = "", Color textColor = { 0,0,0 }, Movability movable = NonMovable, ObjectType objectType = Solid);
	~Player();
	void HandleEvent(SDL_Event & event) override;
	void HandleJump();
	void Reset();
	void GrabLive();
	int GetLivesCount();

private:
	Timer jumpTimer;
	bool jump;
	bool jumping;
	int curY;
	int livesCount;
};

