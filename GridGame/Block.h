
#pragma once

#include "GridGame.h"

class Block {
public:

	int x, y;
	float seed;
	GLfloat z;

	Color topColor;
	Color bottomColor;

	void Init(int x, int y);
	void UpdateHeights();
	void UpdateLighting();

};
