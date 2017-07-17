
#include "Grid.h"

Grid g_grid;

void Grid::Init(){

	int w = MaxWidth;
	for(int i = 0; i < w; i++){
		for(int j = 0; j < w; j++){
			Block& b = blocks[i * w + j];
			b.SetTopColor(glm::vec4(.5f, .5f, .5f, 1.f));
			b.SetBottomColor(glm::vec4(.5f, .5f, .5f, 1.f));

			float x = j - w/2;
			float y = i - w/2;
			b.SetPosition(glm::vec3(x, y, 0));
			b.Draw();
		}
	}
}

void Grid::Draw(){	
		int w = MaxWidth;
		for(int i = 0; i < w; i++){
			for(int j = 0; j < w; j++){
				Block& b = blocks[i * w + j];
				b.Draw();
			}
		}
}

