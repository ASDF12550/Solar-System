

#include "pch.h"
#include "framework.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine, _In_ int       nCmdShow) {
	SDL_Window* window = SDL_CreateWindow("Universe Simulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800, SDL_WINDOW_OPENGL);
	if (!window) return -1;
	IMG_Init(SDL_INIT_VIDEO);
	SDL_Surface* window_surface = SDL_GetWindowSurface(window);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	SDL_GLContext glContext = SDL_GL_CreateContext(window);

	SDL_GL_SetSwapInterval(SDL_FALSE);

	if (!window_surface) return -1;
	cCore core = window;
    return 0;
}
 