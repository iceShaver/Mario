#include "FPSGauge.h"
#include "Program.h"
#include <SDL.h>
#include <stdio.h>

FPSGauge Program::fpsGauge;

int main(int argc, char* argv[])
{
	if (!Program::Init()) Program::EmergencyExit();
	if (!Program::LoadContent()) Program::EmergencyExit();
	Program::fpsGauge.AverageFPSTimerStart();
	while (!Program::quit)
	{
		Program::HandleEvent();
		if (Program::IsGameStarted()) {
			Program::HandleAction();
			Program::camera.SetCamera();
		}
		Program::ClearRenderer();
		if (Program::IsGameStarted())
		{
			Program::Render();
			Program::DisplayInfo();
		}else
		Program::DisplayMenu();
		Program::DisplayDiagnosticInfo();
		SDL_RenderPresent(Program::renderer);
		Program::fpsGauge.FramesCounterIncrease();
		Program::fpsGauge.SetDeltaTime();
		Program::SetDeltaTime();

		Program::fpsGauge.VSync();
	}


	Program::Exit();
	return 0;
}

