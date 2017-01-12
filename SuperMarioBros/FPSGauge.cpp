#include "FPSGauge.h"
#include "Program.h"
#include <stdio.h>
#include "Object.h"

Timer Program::timer;
float Program::deltaTime;
FPSGauge::FPSGauge()
{
	framesCounter = 0;
	currentFPSFramesTime = 1;
	currentFPS = 0;

}


FPSGauge::~FPSGauge()
{
}

void FPSGauge::DisplayAverageFPS(SDL_Color color)
{
	char text[32];
	float fps = framesCounter / (averageFPSTimer.GetTime() / 1000.f);
	sprintf(text, "AVG FPS: %.2f", fps);
	if (!LoadFromRenderedText(text, color))
		printf("Unable to render time texture\n");
	Render(200, 0);
}

void FPSGauge::DisplayCurrentFPS(SDL_Color color)
{
	char text[32];
	currentFPS = 1000*Config::CURRENT_FPS_UPDATE_INTERVAL/currentFPSFramesTime;
	sprintf(text, "CUR FPS: %d", currentFPS);
	if (!LoadFromRenderedText(text, color))
		printf("Unable to render time texture\n");
	Render(320, 0);
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

void FPSGauge::DisplayFramesCount(SDL_Color color)
{
	char text[32];
	sprintf(text, "FPS count: %d", framesCounter);
	if (!LoadFromRenderedText(text, color))
		printf("Unable to render time texture\n");
	Render(80, 0);

}

void FPSGauge::DisplayFrameTime(SDL_Color color)
{
	char text[32];
	sprintf(text, "%d frames time: %d", Config::CURRENT_FPS_UPDATE_INTERVAL, currentFPSFramesTime);
	if (!LoadFromRenderedText(text, color))
		printf("Unable to render time texture\n");
	Render(420, 0);
}



void FPSGauge::DisplayStats()
{
	//SDL_Color color = {0,0,0};
	DisplayAverageFPS();
	DisplayCurrentFPS();
	DisplayFramesCount();
	DisplayFrameTime();
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


