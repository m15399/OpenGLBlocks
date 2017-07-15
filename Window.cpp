
#include "Window.h"

Window g_window;

void Window::Init(){
	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0){
		fprintf(stderr, "Couldn't init SDL: %s\n", SDL_GetError());
		exit(1);
	}

	uint32_t flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
	if(fullscreen){
		flags |= SDL_WINDOW_FULLSCREEN;
	}

	window = SDL_CreateWindow(title,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width,
		height,
		flags);

	glcontext = SDL_GL_CreateContext(window);

	glViewport(0, 0, width, height);
}

void Window::ToggleFullscreen(){
	fullscreen = !fullscreen;
	uint32_t flags = 0;
	if(fullscreen){
		flags = SDL_WINDOW_FULLSCREEN;
	}
	SDL_SetWindowFullscreen(window, flags);
}

void Window::Draw(){
	SDL_GL_SwapWindow(window);
}
