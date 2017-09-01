
#pragma once

#include "SDL.h"

#define SHADER_LIST(F) \
	F(shader1) \
	F(basic) \
	F(basic_color) \
	F(basic_color_tex)

// Uses: 
//	shader.nameLoc - location of the attribute
// 	mesh.nameBuffer
//
#define SHADER_ATTRIB_LIST(F) \
	F(a_position) \
	F(a_normal) \
	F(a_color) \
	F(a_boneIndex) \
	F(a_uv)

#define SHADER_UNIFORM_LIST(F) \
	F(mvp) \
	F(colorTint) \
	F(vOffsets) \
	F(tex)

class Shader {

public:
	static Shader* currShader;

	GLuint program;


	#define DEFINE_SHADER_LOC(name) \
		GLuint name##Loc = 0;

	SHADER_ATTRIB_LIST(DEFINE_SHADER_LOC);
	SHADER_UNIFORM_LIST(DEFINE_SHADER_LOC);

	#undef DEFINE_SHADER_LOC

	bool bound;

	// Looks for shaderName.vert and 
	bool Load(const char* shaderName);
	void Use();
	void Unuse();

	void EnableAttribs();
	void DisableAttribs();

};

class Shaders {
public:
	void Init();

	#define DEFINE_SHADER(name) \
		Shader name;

	SHADER_LIST(DEFINE_SHADER);

	#undef DEFINE_SHADER
};

extern Shaders g_shaders;
