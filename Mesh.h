
#pragma once

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "SDL.h"
#include "Shader.h"

class Mesh {

	GLuint verticesBuffer;
	GLuint colorsBuffer;
	GLuint vOffsetsBuffer;

	GLuint indecesBuffer;
	GLsizei numIndeces;

	bool borrowingVOffsets = false;

public:
	
	void Init();
	
	void CopyVOffsetsBuffer(Mesh& other);

	void Set(const GLfloat* vertices, const GLubyte* colors, int numVertices,
			const GLuint* indeces, int numTris);
	
	void SetVertices(const GLfloat* vertices, int count);
	void SetColors(const GLubyte* colors, int count);
	void SetVOffsets(const GLfloat* offsets, int count);

	void SetIndeces(const GLuint* indeces, int count);

	void Draw(Shader& shader = g_shaders.shader1,
		const glm::mat4& modelMatrix = glm::mat4{1.0},
		const glm::vec4& colorTint = glm::vec4{1.0});

};
