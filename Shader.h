
#pragma once

#include "SDL.h"

class Shader {

public:

	GLuint program;
	GLuint mvpLoc;

	// Looks for shaderName.vert and 
	bool Load(const char* shaderName);
	void Use();

};

class Shaders {
public:
	void Init();

	Shader shader1;
};

extern Shaders g_shaders;
