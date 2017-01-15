#include "Level.h"
#include <string.h>
#include <stdio.h>

Level::Level(const char* name, int groundLevel, int width, int height, int time, int endXPos, int startPlayerXPos, int startPlayerYPos)
{
	printf("New level\n");

	strcpy_s(this->name, Config::LEVEL_NAME_LENGTH, name);
	this->groundLevel = groundLevel;
	this->width = width;
	this->height = height;
	this->time = time;
	this->endXPos = endXPos;
	this->startPlayerXPos = startPlayerXPos;
	this->startPlayerYPos = startPlayerYPos;
}

Level::Level(const char* filePath)
{
	printf("New object\n");

	readFromFile(filePath);
}

Level::~Level()
{
}

int Level::GetGroundLevel() const
{
	return groundLevel;
}

int Level::GetWidth() const
{
	return width;

}

int Level::GetHeight() const
{
	return height;
}

void Level::RenderObjects()
{
	objects.ForEach(&Object::Render);
}

int Level::GetStartPlayerXPos() const
{
	return startPlayerXPos;
}

int Level::GetStartPlayerYPos() const
{
	return startPlayerYPos;
}

int Level::GetEndXPos() const
{
	return endXPos;
}

int Level::GetTime() const
{
	return time;
}

const char* Level::GetName() const
{
	return name;
}

bool Level::readFromFile(const char* path)
{
	FILE *file;
	if((file = fopen(path, "r")) == NULL)
	{
		printf("Unable to read level file: %s\n", path);
		return false;
	}
	fgets(name, Config::LEVEL_NAME_LENGTH, file);
	strtok(name, "\n");
	if (strcmp(name, "\n") == 0)
		strcpy_s(name, Config::LEVEL_NAME_LENGTH, "");
	fscanf(file, "%d%d%d%d%d%d%d", &width, &height, &time, &startPlayerXPos, &startPlayerYPos, &endXPos, &groundLevel);

	/*while(feof(file))
	{
		
	}*/
	fclose(file);
	return true;

}

