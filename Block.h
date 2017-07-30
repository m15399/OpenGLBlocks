
#pragma once

#include "SDL.h"

class Block {
public:

	int x, y;
	GLfloat z;
	GLubyte topColor[4];
	GLubyte bottomColor[4];

	void Init(int x, int y);
	void Update();

};
