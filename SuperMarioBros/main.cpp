#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

int main(int argc, char* argv[])
{
	int s = SDL_Init(SDL_INIT_VIDEO);
	int i = IMG_Init(IMG_INIT_PNG);
	int t = TTF_Init();
	return 0;
}
