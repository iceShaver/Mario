#pragma once
#include "Texture.h"
#include <SDL.h>
#include "Object.h"


class Timer : public Object
{
public:
	Timer();
	~Timer();
	void Start();
	void Stop();
	void Pause();
	void Resume();
	Uint32 GetTime() const;
	Uint32 GetSeconds() const;
	bool IsStarted() const;
	bool IsPaused() const;

private:
	Uint32 startTime;
	Uint32 pausedTime;
	bool paused;
	bool started;

};

