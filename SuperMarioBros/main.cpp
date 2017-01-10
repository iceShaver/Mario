#include <SDL.h>
#include "Program.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <conio.h>
FPSGauge Program::fpsGauge;

int main(int argc, char* argv[])
{
	if (!Program::Init()) Program::EmergencyExit();
	if (!Program::LoadContent()) Program::EmergencyExit();
	Program::fpsGauge.AverageFPSTimerStart();

	while (!Program::quit)
	{
		Program::fpsGauge.currentFPSTimerStart();
		Program::HandleEvent();
		Program::HandleAction();
		Program::ClearRenderer();


		Program::fpsGauge.DisplayAverageFPS();
		Program::fpsGauge.DisplayCurrentFPS();
		SDL_RenderPresent(Program::renderer);
		Program::framesCounter++;
		Program::fpsGauge.SetFrameTime();
	}


	Program::Exit();
	return 0;
}
