#include "FPSGauge.h"
#include "Program.h"


FPSGauge::FPSGauge():Timer()
{

}


FPSGauge::~FPSGauge()
{
}

void FPSGauge::DisplayFPS()
{
	char text[32];
	float fps = Program::framesCounter / (GetTime()/1000.f);
	sprintf(text, "FPS: %f", fps);
	if (!LoadFromRenderedText(text, { 0,0,0 }))
		printf("Unable to render time texture\n");
	Render(0, 0);
}
