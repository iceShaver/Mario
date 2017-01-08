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
	Program::fpsGauge.Start();

	while (!Program::quit)
	{
		Program::HandleEvent();
		Program::HandleAction();
		Program::ClearRenderer();



		Program::fpsGauge.DisplayFPS();
		SDL_RenderPresent(Program::renderer);
		Program::framesCounter++;
	}


	Program::Exit();
	return 0;
}
