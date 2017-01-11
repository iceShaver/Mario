#include "FPSGauge.h"
#include "Program.h"

Timer Program::timer;
FPSGauge::FPSGauge()
{
	framesCounter = 0;
	startFrameTime = 0;
	endFrameTime = 0;
	deltaFrameTime = 1;
	currentFPS = 0;


}


FPSGauge::~FPSGauge()
{
}

void FPSGauge::DisplayAverageFPS()
{
	char text[32];
	float fps = framesCounter / (averageFPSTimer.GetTime() / 1000.f);
	sprintf(text, "AVG FPS: %.2f", fps);
	if (!LoadFromRenderedText(text, { 0xff,0xff,0xff }))
		printf("Unable to render time texture\n");
	Render(200, 0);
}

void FPSGauge::DisplayCurrentFPS()
{
	char text[32];
	currentFPS = 1000*Config::CURRENT_FPS_UPDATE_INTERVAL/deltaFrameTime;
	sprintf(text, "CUR FPS: %d", currentFPS);
	if (!LoadFromRenderedText(text, { 0xff,0xff,0xff }))
		printf("Unable to render time texture\n");
	Render(320, 0);
}

void FPSGauge::AverageFPSTimerStart()
{
	averageFPSTimer.Start();
}



void FPSGauge::SetStartupFrameTime()
{
	if (framesCounter%Config::CURRENT_FPS_UPDATE_INTERVAL == 0)
		startFrameTime = Program::timer.GetTime();
}



void FPSGauge::FramesCounterIncrease()
{
	framesCounter++;
}

void FPSGauge::DisplayFramesCount()
{
	char text[32];
	sprintf(text, "FPS count: %d", framesCounter);
	if (!LoadFromRenderedText(text, { 0xff,0xff,0xff }))
		printf("Unable to render time texture\n");
	Render(80, 0);

}

void FPSGauge::DisplayFrameTime()
{
	char text[32];
	sprintf(text, "%d rames time: %d", Config::CURRENT_FPS_UPDATE_INTERVAL, deltaFrameTime);
	if (!LoadFromRenderedText(text, { 0xff,0xff,0xff }))
		printf("Unable to render time texture\n");
	Render(420, 0);
}

void FPSGauge::SetDeltaTime()
{
	if (framesCounter % Config::CURRENT_FPS_UPDATE_INTERVAL == 0)
	{
		endFrameTime = Program::timer.GetTime();
		deltaFrameTime = endFrameTime - startFrameTime;
	}
}

void FPSGauge::DisplayStats()
{
	DisplayAverageFPS();
	DisplayCurrentFPS();
	DisplayFramesCount();
	//DisplayFrameTime();
}


