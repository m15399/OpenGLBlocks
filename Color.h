
#pragma once

#include "SDL.h"

class Color{
public:

	GLubyte r = 0, g = 0, b = 0, a = 0;

	Color();
	Color(GLubyte r, GLubyte g, GLubyte b, GLubyte a);

	GLubyte& operator[](int i);
	Color operator*(float v);

	void Set(GLubyte r, GLubyte g, GLubyte b, GLubyte a);

	Color Lerp(const Color& other, float t);

	void Brighten(float amt);

};
