#pragma once
#include "Object.h"
//class Object::HandleEvent;
class Player : public Object
{
public:
	Player();
	~Player();
	bool Render() override;
	bool LoadContent() override;
};

