
#include <cmath>

#include "Block.h"
#include "Time.h"
#include "Utils.h"

void Block::Init(int x2, int y2){
	x = x2;
	y = y2;

	seed = Random(0.f, 1.f);

	topColor[0] = 100;
	topColor[1] = 185;
	topColor[2] = 105;
	topColor[3] = 255;

	bottomColor[0] = 80;
	bottomColor[1] = 160;
	bottomColor[2] = 140;
	bottomColor[3] = 255;

}

void Block::Update(){
	float t = (g_time.time % 1000000) / 1000.f + x/10.f + y/4.f;
	// t = (x) * 1.1f;
	z = (GLfloat)(std::sin(t) * 1.5f);
	z = 0;
	// z += seed * .2;
}
