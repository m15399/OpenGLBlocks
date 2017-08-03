
#include <cmath>

#include "Block.h"
#include "Time.h"
#include "Utils.h"
#include "Grid.h"

void Block::Init(int x2, int y2){
	x = x2;
	y = y2;

	seed = Random(0.f, 1.f);

	// topColor[0] = 100;
	// topColor[1] = 185;
	// topColor[2] = 105;
	// topColor[3] = 255;

	bottomColor[0] = 80;
	bottomColor[1] = 160;
	bottomColor[2] = 140;
	bottomColor[3] = 255;

}

void Block::UpdateHeights(){
	float t = (g_time.time % 1000000) / 1000.f + x/10.f + y/4.f;
	// t = (x) * 1.1f;
	z = 0;
	z = (GLfloat)(std::sin(t) * .25f);
	// z = 0;
	z += seed * .2 * .25;
}

void Block::UpdateLighting(){
	topColor[0] = 100;
	topColor[1] = 185;
	topColor[2] = 105;
	topColor[3] = 255;

	float fac = 5.0;
	float spread = 2.0;
	float exp = .5;

	Block* rightBlock = g_grid.GetBlock(x + 1, y);
	Block* topBlock = g_grid.GetBlock(x, y + 1);

	// TODO reduce the effect of the seed (have a basez)

	float dh = 0;

	if(rightBlock){
		dh = z - rightBlock->z;
	}
	if(topBlock){
		float dh2 = z - topBlock->z;
		dh = (dh + dh2) / 2;
	}
	
	float adj01 = Clamp(dh, -spread, spread) / spread;
	float adj = adj01 * fac + 1;
	
	adj = std::pow(adj, exp);

	for(int i = 0; i < 3; i++)
		topColor[i] = (GLubyte) Clamp((topColor[i] * adj), 0, 255);		
}
