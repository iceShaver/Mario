#pragma once
#include "List.h"
#include "Object.h"

class Level
{
public:
	friend class Object;
	Level(const char * name, int groundLevel, int width, int height, int time, int endXPos, int startPlayerXPos, int startPlayerYPos);
	Level(const char * filePath);
	~Level();
	int GetGroundLevel() const;
	static void LoadLevels();
	int GetWidth() const;
	int GetHeight() const;
	void RenderObjects();
	int GetStartPlayerXPos() const;
	int GetStartPlayerYPos() const;
	int GetEndXPos() const;
	int GetTime() const;
	bool GetNext();
	void LevelCompleted();
	const char * GetName() const;
	bool Uncomplete();
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
	bool completed;
	char name[Config::LEVEL_NAME_LENGTH];

	//char filePath[Config::LEVEL_FILE_PATH_LENGTH];
};

