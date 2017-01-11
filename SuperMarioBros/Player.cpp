#include "Player.h"
#include "Object.h"
#include "stdio.h"
#include "Config.h"
Player::Player() : Object()
{
}


Player::~Player()
{
}

bool Player::Render()
{
	render(xPos, yPos);
	return true;
}


bool Player::LoadContent()
{
	if (!getTextureFromFile("textures/dot.bmp", 0 , 0xff, 0xff)) return false;
	printf("Dot content loaded\n");
	return true;

}


