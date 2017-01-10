#include "Timer.h"



Timer::Timer()
{
	startTime = 0;
	pausedTime = 0;
	paused = false;
	started = false;
}


Timer::~Timer()
{
}

void Timer::Start()
{
	started = true;
	paused = false;
	startTime = SDL_GetTicks();
	pausedTime = 0;
}

void Timer::Stop()
{
	started = false;
	paused = false;
	startTime = 0;
	pausedTime = 0;
}

void Timer::Pause()
{
	if (started && !paused)
	{
		paused = true;
		pausedTime = SDL_GetTicks() - startTime;
		startTime = 0;
	}
}

void Timer::Resume()
{
	if (started && paused)
	{
		paused = false;
		startTime = SDL_GetTicks() - pausedTime;
		pausedTime = 0;
	}
}


Uint32 Timer::GetTime() const
{
	Uint32 time = 0;
	if (started)
		if (paused)
			return pausedTime;
	return SDL_GetTicks() - startTime;
}

bool Timer::IsStarted() const
{
	return started;
}

bool Timer::IsPaused() const
{
	return paused;
}
