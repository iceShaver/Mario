#include "Camera.h"
#include <cstdio>
#include "Program.h"


Camera::Camera()
{
	printf("New camera\n");

	camera = { 0,0,Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT };
}


Camera::~Camera()
{
}

void Camera::Follow(Object* object)
{
	this->object = object;
}

void Camera::SetCamera()
{
	camera.x = (object->GetXPos() + object->GetWidth() / 2) - Config::SCREEN_WIDTH / 2;
	camera.y = (object->GetYPos() + object->GetHeight() / 2) - Config::SCREEN_HEIGHT / 2;

	if (camera.x < 0) camera.x = 0;
	if (camera.y < 0) camera.y = 0;
	if (camera.x + camera.w > Program::loadedLevel->GetWidth()) camera.x = Program::loadedLevel->GetWidth() - camera.w;
	if (camera.y + camera.h > Program::loadedLevel->GetHeight()) camera.y = Program::loadedLevel->GetHeight() - camera.h;
}

int Camera::GetXPos() const
{
	return camera.x;
}

int Camera::GetYPos() const
{
	return camera.y;
}

int Camera::GetWidth() const
{
	return camera.w;
}

int Camera::GetHeight() const
{
	return camera.h;
}
