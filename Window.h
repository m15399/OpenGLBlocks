
#pragma once

#include "SDL.h"


class Window {

	SDL_Window* window;
	SDL_GLContext glcontext;

public:

	const char* title = "SDL Test";
	int width = 640;
	int height = 320;
	bool fullscreen = false;
	bool lockedFramerate = true;

	void Init();

	void Resize(int width, int height);

	void ToggleFullscreen();
	void ToggleUnlockedFramerate();

	void Draw();

};

extern Window g_window;
