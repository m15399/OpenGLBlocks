
#pragma once

#include <glm/vec4.hpp>

#include "../SDL.h"
#include "../Color.h"

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
