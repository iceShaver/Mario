#include <SDL.h>
#include "Program.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <conio.h>
#include <string.h>
#include "List.h"
#include "Object.h"
#include "Background.h"
#include <list>
FPSGauge Program::fpsGauge;

int main(int argc, char* argv[])
{
	if (!Program::Init()) Program::EmergencyExit();
	if (!Program::LoadContent()) Program::EmergencyExit();
	Program::fpsGauge.AverageFPSTimerStart();
	Program::timer.Start();
	while (!Program::quit)
	{
		Program::fpsGauge.SetStartupFrameTime();
		Program::HandleEvent();
		Program::HandleAction();
		Program::ClearRenderer();

		Program::fpsGauge.DisplayStats();
		
		Program::timer.DisplayTime();




		SDL_RenderPresent(Program::renderer);
		Program::fpsGauge.FramesCounterIncrease();
		Program::fpsGauge.SetDeltaTime();
	}


	Program::Exit();

	return 0;
}

