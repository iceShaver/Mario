#include "FPSGauge.h"
#include "Program.h"
#include <SDL.h>

FPSGauge Program::fpsGauge;

int main(int argc, char* argv[])
{
	if (!Program::Init()) Program::EmergencyExit();
	if (!Program::LoadContent()) Program::EmergencyExit();
	Program::fpsGauge.AverageFPSTimerStart();
	while (!Program::quit)
	{
		Program::HandleEvent();
		Program::HandleAction();
		Program::camera.SetCamera();
		Program::ClearRenderer();
		Program::Render();
		Program::fpsGauge.DisplayStats();
		Program::timer.DisplayTime();
		Program::DisplayPlayerXY();
		SDL_RenderPresent(Program::renderer);
		Program::fpsGauge.FramesCounterIncrease();
		Program::fpsGauge.SetDeltaTime();
		Program::SetDeltaTime();

		Program::fpsGauge.VSync();
	}


	Program::Exit();
	return 0;
}

