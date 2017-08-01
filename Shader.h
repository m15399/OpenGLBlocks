
#pragma once

#include "SDL.h"

// Uses: 
//	shader.nameLoc - location of the attribute
// 	mesh.nameBuffer
//
#define SHADER_ATTRIB_LIST(F) \
	F(a_position) \
	F(a_normal) \
	F(a_color) \
	F(a_boneIndex)

#define SHADER_UNIFORM_LIST(F) \
	F(mvp) \
	F(colorTint) \
	F(vOffsets)

class Shader {

public:
	static Shader* currShader;

	GLuint program;


	#define DEFINE_SHADER_LOC(name) \
		GLuint name##Loc;

	SHADER_ATTRIB_LIST(DEFINE_SHADER_LOC);
	SHADER_UNIFORM_LIST(DEFINE_SHADER_LOC);

	#undef DEFINE_SHADER_LOC

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
