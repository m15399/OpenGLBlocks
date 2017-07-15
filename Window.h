
#pragma once

#include "SDL.h"


class Window {

	SDL_Window* window;
	SDL_GLContext glcontext;

public:

	const char* title = "SDL Test";
	int width = 640;
	int height = 480;
	bool fullscreen = false;

	void Init();

	void ToggleFullscreen();

	void Draw();

};

extern Window g_window;
