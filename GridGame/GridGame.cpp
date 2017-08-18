
#include <thread>
#include <atomic>
#include <vector>

#include "GridGame.h"
#include "Grid.h"
#include "Player.h"
#include "../Camera.h"

/*

TODO

switch back to a shared vOffset buffer?
some sort of vertexdata class
	allocate based on verts, faces
	push vert, push face functions
	update colors
	update buffers (only updates what was changed)
ridiculous cpu usage when not focused
threading
	update 1/4 blocks, push 1/4 geometry...
	only update visible blocks
task system?

fix fullscreen
high dpi

*/


void GridGame::Init(){
	g_grid.Init();
	g_camera.defaultCameraDistance = defaultCameraDistance;
	g_camera.CenterOn(glm::vec3(0, 0, 0), defaultCameraDistance);
}

void GridGame::Update(){
	g_player.Update();
#if 1
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
		// UpdateGridChunk();
	}
	for(auto& thread : threads){
		thread.join();
	}

	g_grid.PushMeshes();
#endif

	float x = g_grid.viewOffsetX;
	float y = g_grid.viewOffsetY;
	g_camera.CenterOn(glm::vec3(x, y, 0));
}

void GridGame::Draw(){
	// TODO redundant
	glClearColor(0, .25, .45, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	g_grid.Draw();
	g_player.Draw();
}
