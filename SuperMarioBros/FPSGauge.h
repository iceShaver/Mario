#pragma once
#include "Timer.h"
#include "Texture.h"

class FPSGauge :
	public Texture
{
public:
	FPSGauge();
	~FPSGauge();
	void DisplayAverageFPS();
	void DisplayCurrentFPS();
	void AverageFPSTimerStart();
	void currentFPSTimerStart();
	void SetFrameTime();
	Uint32 GetFrameTime();
private:
	Timer averageFPSTimer;
	Timer currentFPStimer;
	float currentFPS;
	Uint32 frameTime;
};

