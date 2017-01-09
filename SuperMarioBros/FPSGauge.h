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
private:
	Timer averageFPSTimer;
	Timer currentFPStimer;
};

