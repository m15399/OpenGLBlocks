
#include "SDL.h"
#include "Window.h"
#include "Primitives.h"
#include "Grid.h"
#include "Shader.h"
#include "Camera.h"
#include "Time.h"

bool running = true;

int main(){

	g_window.Init();
	g_shaders.Init();
	g_time.Init();
	g_primitives.Init();
	g_camera.Init();
	g_grid.Init();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	while(running){
		g_time.Update();
		
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

		g_camera.CenterOn(glm::vec3(0, 0, -3), 35);

		g_grid.Draw();

		g_window.Draw();

		// TODO new key only
		if(keys[SDL_SCANCODE_F1]){
			g_window.ToggleFullscreen();
		}
	}

	SDL_Quit();
	return 0;
}
