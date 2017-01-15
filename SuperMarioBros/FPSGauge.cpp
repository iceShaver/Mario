#include "FPSGauge.h"
#include "Program.h"
#include <stdio.h>
#include "Object.h"

Timer Program::timer;
float Program::deltaTime;
FPSGauge::FPSGauge() : Object(0, 0, Fixed)
{
	printf("New fpsg\n");

	framesCounter = 0;
	currentFPSFramesTime = 1;
	currentFPS = 0;

}


FPSGauge::~FPSGauge()
{
}


void FPSGauge::AverageFPSTimerStart()
{
	averageFPSTimer.Start();
}





void FPSGauge::SetDeltaTime()
{
	if (framesCounter % Config::CURRENT_FPS_UPDATE_INTERVAL == 0)
	{
		
		currentFPSFramesTime = currentFPSTimer.GetTime();
		currentFPSTimer.Start();
	}
}

void FPSGauge::FramesCounterIncrease()
{
	framesCounter++;
}


float FPSGauge::GetAverageFPS() const
{
	return framesCounter / (averageFPSTimer.GetTime() / 1000.f);
	
}

float FPSGauge::GetCurrentFPS() const
{
	return 1000 * Config::CURRENT_FPS_UPDATE_INTERVAL / currentFPSFramesTime;
	
}

int FPSGauge::GetFramesCount() const
{
	return framesCounter;
}






void FPSGauge::VSync()
{
	if (Config::FPS_LOCK) {
		double frameTime = vSyncTimer.GetTime();
		if (frameTime < Config::VSYNC_REQUIRED_FRAME_TIME)
			SDL_Delay(Config::VSYNC_REQUIRED_FRAME_TIME - frameTime);
		vSyncTimer.Start();
	}
}


