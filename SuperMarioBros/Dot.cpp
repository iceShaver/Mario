#include "Dot.h"
#include "Object.h"
Dot::Dot() : Object()
{
}


Dot::~Dot()
{
}

bool Dot::LoadContent()
{
	if (!getTextureFromFile("textures/dot.png")) return false;

}
