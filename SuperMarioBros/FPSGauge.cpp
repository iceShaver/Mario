#include "FPSGauge.h"
#include "Program.h"


FPSGauge::FPSGauge()
{

}


FPSGauge::~FPSGauge()
{
}

void FPSGauge::DisplayAverageFPS()
{
	char text[32];
	float fps = Program::framesCounter / (averageFPSTimer.GetTime()/1000.f);
	sprintf(text, "AVG FPS: %f", fps);
	if (!LoadFromRenderedText(text, { 0,0,0 }))
		printf("Unable to render time texture\n");
	Render(0, 0);
}

void FPSGauge::DisplayCurrentFPS()
{
	char text[32];
	float fps = currentFPStimer.GetTime()*1000;
	sprintf(text, "CUR FPS: %f", fps);
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
	currentFPStimer.Start();
}
