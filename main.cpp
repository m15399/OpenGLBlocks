
#include "SDL.h"
#include "Window.h"
#include "Primitives.h"
#include "Shader.h"
#include "Camera.h"

bool running = true;

int main(){

	g_window.Init();
	g_shaders.Init();
	g_primitives.Init();
	g_camera.Init();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	while(running){
		SDL_Event event;
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					running = false;
					break;
				default:
					break;
			}
		}

		const uint8_t* keys = SDL_GetKeyboardState(nullptr);

		if(keys[SDL_SCANCODE_ESCAPE]){
			running = false;
		}

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		g_primitives.square.Draw();
		g_primitives.tube.Draw();

		g_window.Draw();

		// TODO new key only
		if(keys[SDL_SCANCODE_F1]){
			g_window.ToggleFullscreen();
		}
	}

	SDL_Quit();
	return 0;
}
