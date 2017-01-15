#pragma once
#include "Texture.h"
#include <SDL.h>
#include "Timer.h"
class FPSGauge :
	public Object
{
public:
	FPSGauge();
	~FPSGauge();
	float GetAverageFPS();
	float GetCurrentFPS();
	int GetFramesCount();
	void AverageFPSTimerStart();
	void FramesCounterIncrease();
	void SetDeltaTime();
	void VSync();


private:
	float currentFPSFramesTime;
	Uint32 framesCounter;
	Timer averageFPSTimer;
	Timer currentFPSTimer;
	Timer vSyncTimer;
	Uint32 currentFPS;
};

