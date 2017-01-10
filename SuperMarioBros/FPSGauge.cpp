#include "FPSGauge.h"
#include "Program.h"


FPSGauge::FPSGauge()
{
	frameTime = 1;

}


FPSGauge::~FPSGauge()
{
}

void FPSGauge::DisplayAverageFPS()
{
	char text[32];
	float fps = Program::framesCounter / (averageFPSTimer.GetTime() / 1000.f);
	sprintf(text, "AVG FPS: %f", fps);
	if (!LoadFromRenderedText(text, { 0,0,0 }))
		printf("Unable to render time texture\n");
	Render(0, 0);
}

void FPSGauge::DisplayCurrentFPS()
{
	char text[32];
	if (Program::framesCounter % Config::CURRENT_FPS_UPDATE_INTERVAL == 0)
		currentFPS = 1000 * Config::CURRENT_FPS_UPDATE_INTERVAL / (float)frameTime;
	sprintf(text, "CUR FPS: %f", currentFPS);
	if (!LoadFromRenderedText(text, { 0,0,0 }))
		printf("Unable to render time texture\n");
	Render(0, 30);
}

void FPSGauge::AverageFPSTimerStart()
{
	averageFPSTimer.Start();
}

void FPSGauge::currentFPSTimerStart()
{
	if (Program::framesCounter % Config::CURRENT_FPS_UPDATE_INTERVAL == 0)
		currentFPStimer.Start();
}

void FPSGauge::SetFrameTime()
{
	if (Program::framesCounter % Config::CURRENT_FPS_UPDATE_INTERVAL == 0)
		frameTime = currentFPStimer.GetTime();
}


