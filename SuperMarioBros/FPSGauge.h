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
	void DisplayAverageFPS();
	void DisplayCurrentFPS();
	void DisplayFramesCount();
	void DisplayFrameTime();
	void AverageFPSTimerStart();
	void SetStartupFrameTime();
	void FramesCounterIncrease();
	void SetDeltaTime();
	void DisplayStats();
private:
	Uint32 framesCounter;
	Uint32 startFrameTime;
	Uint32 endFrameTime;
	Uint32 deltaFrameTime;
	Timer averageFPSTimer;
	Uint32 currentFPS;
};

