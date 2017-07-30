
#include <cmath>

#include "Block.h"
#include "Time.h"

void Block::Init(int x2, int y2){
	x = x2;
	y = y2;

	topColor[0] = 120;
	topColor[1] = 180;
	topColor[2] = 255;
	topColor[3] = 255;

	bottomColor[0] = 120;
	bottomColor[1] = 180;
	bottomColor[2] = 225;
	bottomColor[3] = 255;

}

void Block::Update(){
	float t = (g_time.time % 1000000) / 1000.f;
	// t = (x + y) * .1f;
	z = (GLfloat)(std::sin(t + x/10.f + y/4.f) * 1.0f);
}
