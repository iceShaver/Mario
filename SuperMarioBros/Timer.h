#pragma once
#include <SDL.h>
class Timer
{
public:
	Timer();
	~Timer();
	void Start();
	void Stop();
	void Pause();
	void Resume();
	Uint32 GetTime() const;
	bool IsStarted() const;
	bool IsPaused() const;
private:
	Uint32 startTime;
	Uint32 pausedTime;
	bool paused;
	bool started;
};

