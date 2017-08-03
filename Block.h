
#pragma once

#include "SDL.h"

class Block {
public:

	int x, y;
	float seed;
	GLfloat z;
	GLubyte topColor[4];
	GLubyte bottomColor[4];

	void Init(int x, int y);
	void UpdateHeights();
	void UpdateLighting();

};
