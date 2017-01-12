#pragma once
#include "Object.h"
#include "Timer.h"

//class Object::HandleEvent;
class Player : public Object
{
public:
	Player(int xPos, int yPos, const char * textureFileName, Movability movable = NonMovable, ObjectType objectType = Solid, Transparency transparency = Transparent, Color transparencyColor = { 0,0,0 });
	Player(int xPos, int yPos, Color textColor = { 0,0,0 }, Movability movable = NonMovable, ObjectType objectType = Solid);
	~Player();
	void HandleEvent(SDL_Event & event) override;
	void HandleJump();

private:
	Timer jumpTimer;
	bool jump;
};

