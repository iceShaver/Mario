#pragma once
#include "SDL.h"
#include "Object.h"

class Camera
{
public:
	Camera();
	~Camera();
	void Follow(Object * object);
	void SetCamera();
	int GetXPos() const;
	int GetYPos() const;
	int GetWidth() const;
	int GetHeight() const;
private:
	SDL_Rect camera;
	Object * object;
};

