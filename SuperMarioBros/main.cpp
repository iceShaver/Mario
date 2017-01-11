#include "FPSGauge.h"
#include "Program.h"
#include <SDL.h>

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
		Program::Render();
		Program::fpsGauge.DisplayStats();
		
		Program::timer.DisplayTime();




		SDL_RenderPresent(Program::renderer);
		Program::fpsGauge.FramesCounterIncrease();
		Program::fpsGauge.SetDeltaTime();
	}


	Program::Exit();

	return 0;
}

