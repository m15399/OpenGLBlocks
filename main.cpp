
/*

TODO

resizing window
	high dpi too
special frag shader for block top
block bottom shader
use Block objects for state
	2 colors & height per block
alpha fading on edges
moving camera (grid window follows)
go back to using vOffset buffer? no uniform limits

*/

#include <unistd.h> // for sleeping
#include <iostream>

#include "SDL.h"
#include "Window.h"
#include "Primitives.h"
#include "Grid.h"
#include "Shader.h"
#include "Camera.h"
#include "Time.h"
#include "Input.h"

bool running = true;

int main(){

	g_window.Init();
	g_input.Init();
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
		g_input.Update();
		g_time.Update();

		SDL_Event event;
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					running = false;
					break;
				case SDL_KEYDOWN:
				case SDL_KEYUP:
					g_input.UpdateKey(event.key);
					break;
				default:
					break;
			}
		}

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		g_camera.CenterOn(glm::vec3(0, 0, -3), 1 * 35.f);

		g_grid.Draw();

		g_window.Draw();

		if(g_input.KeyPressed(SDL_SCANCODE_F1)){
			g_window.ToggleFullscreen();
		}
		if(g_input.KeyPressed(SDL_SCANCODE_F2)){
			g_window.ToggleUnlockedFramerate();
		}
		if(g_input.KeyPressed(SDL_SCANCODE_ESCAPE)){
			running = false;
		}
	}

	SDL_Quit();
	return 0;
}
