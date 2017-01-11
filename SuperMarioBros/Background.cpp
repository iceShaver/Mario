#include "Background.h"
#include <stdio.h>
bool Background::Render()
{
	render(0, 0);
	return true;
}

bool Background::LoadContent()
{
	getTextureFromFile("textures/background.png");
	printf("Background texture content loaded\n");
	return true;
	
}

Background::Background()
{
	
}


Background::~Background()
{
}
