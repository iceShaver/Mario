#pragma once
#include "List.h"
#include "Object.h"

class Level
{
public:
	Level(const char * name, int groundLevel, int width, int height, int time, int endXPos, int startPlayerXPos, int startPlayerYPos);
	Level(const char * filePath);
	~Level();
	int GetGroundLevel() const;
	static List<Level> LoadLevels();
	int GetWidth() const;
	int GetHeight() const;
	void RenderObjects();
	int GetStartPlayerXPos() const;
	int GetStartPlayerYPos() const;
	int GetEndXPos() const;
	int GetTime() const;
	const char * GetName() const;
private:
	bool readFromFile(const char * path);
	int groundLevel;
	int width;
	int height;
	List<Object> objects;
	int startPlayerXPos;
	int startPlayerYPos;
	int endXPos;
	int time;
	char name[Config::LEVEL_NAME_LENGTH];
	//char filePath[Config::LEVEL_FILE_PATH_LENGTH];
};

