
/*

TODO

block bottom shader
	pass normals
ridiculous cpu usage when not focused
use triangle strips for grid
threading
	update 1/4 blocks, push 1/4 geometry...
	only update visible blocks
task system?

fix fullscreen
high dpi

*/

#include <iostream>
#include <thread>
#include <atomic>
#include <vector>

#include "SDL.h"
#include "Window.h"
#include "Primitives.h"
#include "Grid.h"
#include "Shader.h"
#include "Camera.h"
#include "Time.h"
#include "Input.h"
#include "Globals.h"

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
	 // TODO this isn't quite right
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);


	while(running){
		g_input.Update();
		g_time.Update();

		SDL_Event event;
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					running = false;
					break;
				case SDL_WINDOWEVENT:
					switch(event.window.event) {
						case SDL_WINDOWEVENT_SIZE_CHANGED:
							g_window.Resize(event.window.data1, event.window.data2);
							break;
					}
				case SDL_KEYDOWN:
				case SDL_KEYUP:
					g_input.UpdateKey(event.key);
					break;
				default:
					break;
			}
		}

		glClearColor(0, .25, .45, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Update
		{
#if 0
			g_grid.Update();

			std::atomic<int> chunk;
			chunk = 0;
			constexpr int numChunks = 4;
			
			auto UpdateGridChunk = [&chunk, numChunks](){
				g_grid.UpdateMeshes(chunk++, numChunks);
			};

			std::vector<std::thread> threads;
			threads.reserve(numChunks);

			for(int i = 0; i < numChunks; i++){
				threads.emplace_back(UpdateGridChunk);
			}
			for(int i = 0; i < numChunks; i++){
				threads[i].join();
			}

			g_grid.PushMeshes();
#endif


			g_camera.Update();
		}

		// Draw
		{
			// g_grid.Draw();

			g_primitives.cube.Draw(g_shaders.shader1);

			g_window.Draw();
		}

		if(g_input.KeyPressed(SDL_SCANCODE_GRAVE)){
			g_globals.debug = !g_globals.debug;
			std::cout << "Debug = " << g_globals.debug << "\n";
		}
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
