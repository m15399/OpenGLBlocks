
#pragma once

#include "SDL.h"

class Mesh {

	#define DEFINE_SHADER_BUFFER(name) \
		GLuint name##Buffer;

	SHADER_ATTRIB_LIST(DEFINE_SHADER_BUFFER);

	#undef DEFINE_SHADER_BUFFER


	GLuint indecesBuffer;
	GLsizei numIndeces;
	bool usingIndeces = false;

	GLsizei verticesLen;

	bool borrowingVOffsets = false;

public:
	
	void Init();
		
	void SetVertices(const GLfloat* vertices, int count);
	void SetColors(const GLubyte* colors, int count);
	void SetBoneIndeces(const GLushort* indeces, int count);
	void SetVOffsets(const GLfloat* offsets, int count);

	void SetIndeces(const GLuint* indeces, int count);

	void Draw(Shader& shader = g_shaders.shader1,
		const glm::mat4& modelMatrix = glm::mat4{1.0},
		const glm::vec4& colorTint = glm::vec4{1.0},
		Texture* texture = nullptr);

};
