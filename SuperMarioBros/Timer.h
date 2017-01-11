#pragma once
#include "Texture.h"
#include <SDL.h>


class Timer : public Texture
{
public:
	Timer();
	~Timer();
	void Start();
	void Stop();
	void Pause();
	void Resume();
	void DisplayTime();
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

