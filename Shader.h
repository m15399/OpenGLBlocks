
#pragma once

#include "SDL.h"

class Shader {

public:
	static Shader* currShader;

	GLuint program;
	GLuint mvpLoc;
	GLuint colorTintLoc;

	GLuint positionAttrib;
	GLuint colorAttrib;

	bool bound;

	// Looks for shaderName.vert and 
	bool Load(const char* shaderName);
	void Use();
	void Unuse();

};

class Shaders {
public:
	void Init();

	Shader shader1;
};

extern Shaders g_shaders;
