#pragma once
#include "Object.h"
//class Object::HandleEvent;
class Dot : public Object
{
public:
	Dot();
	~Dot();
	bool LoadContent() override;
};

