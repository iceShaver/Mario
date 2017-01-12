#pragma once
#include "Texture.h"
#include <SDL.h>
#include "Timer.h"
class FPSGauge :
	public Texture
{
public:
	FPSGauge();
	~FPSGauge();
	void DisplayAverageFPS(SDL_Color color = { 0,0,0 });
	void DisplayCurrentFPS(SDL_Color color = { 0,0,0 });
	void DisplayFramesCount(SDL_Color color = { 0,0,0 });
	void DisplayFrameTime(SDL_Color color = { 0,0,0 });
	void AverageFPSTimerStart();
	void FramesCounterIncrease();
	void SetDeltaTime();
	void DisplayStats();
	void VSync();


private:
	Uint32 currentFPSFramesTime;
	Uint32 framesCounter;
	Timer averageFPSTimer;
	Timer currentFPSTimer;
	Timer vSyncTimer;
	Uint32 currentFPS;
};

