#include "Level.h"
#include <string.h>
#include <stdio.h>
#include "Program.h"
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

List<Level> Level::LoadLevels()
{
	List<Level> list;
	return list;
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
	groundLevel = height - groundLevel;
	while(!feof(file))
	{
		int x, y;
		char name[Config::OBJECT_NAME_LENGTH];
		char texture[Config::TEXTURE_FILE_NAME_LENGTH];
		fscanf(file, "%s%s%d%d", name, texture, &x, &y);
		Object * object = new Object(x, y, Program::textures.Get(texture), name, Object::NonMovable, Object::Solid, Object::NonRepeatable);
		//objects.Add(object);
		Program::objects.Add(object);
	}

	fclose(file);
	return true;

}

