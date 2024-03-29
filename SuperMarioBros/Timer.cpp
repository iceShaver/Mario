#include "Timer.h"
#include <SDL.h>
#include <stdio.h>
#include "Object.h"
Timer::Timer() :Object(0,0, Fixed)
{
	
	startTime = 0;
	pausedTime = 0;
	paused = false;
	started = false;
	printf("New timer\n");

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
	if (started)
		if (paused)
			return pausedTime;
	return SDL_GetTicks() - startTime;
}

Uint32 Timer::GetSeconds() const
{
	if (started)
		if (paused)
			return pausedTime/1000;
	return (SDL_GetTicks() - startTime)/1000;
}

bool Timer::IsStarted() const
{
	return started;
}

bool Timer::IsPaused() const
{
	return paused;
}
