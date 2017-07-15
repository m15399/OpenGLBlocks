
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Primitives.h"
#include "SDL.h"
#include "Shader.h"

Primitives g_primitives;

class Mesh {

	GLuint verticesBuffer;
	GLuint colorsBuffer;
	GLuint indecesBuffer;
	GLsizei numVertices;

public:
	
	void Init();	
	void SetVertices(const GLfloat* vertices, int count);
	void SetColors(const GLfloat* colors, int count);
	void SetIndeces(const GLushort* indeces, int count);
	void Draw();

};

void Mesh::Init(){
	glGenBuffers(1, &verticesBuffer);
	glGenBuffers(1, &colorsBuffer);
	glGenBuffers(1, &indecesBuffer);
}

// Count is vertices.length - not number of vertices
//
void Mesh::SetVertices(const GLfloat* vertices, int count){
	glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
}

void Mesh::SetColors(const GLfloat* colors, int count){
	glBindBuffer(GL_ARRAY_BUFFER, colorsBuffer);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), colors, GL_STATIC_DRAW);
}

// Count is indeces.length
//
void Mesh::SetIndeces(const GLushort* indeces, int count){
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indecesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), indeces, GL_STATIC_DRAW);
	numVertices = (GLsizei) count;
}

void Mesh::Draw(){
	glm::mat4 Proj = glm::perspective(glm::radians(45.0f), 1.33f, .1f, 1000.f);
	float d = 5;
	glm::vec3 eye(-d, -d, d);
	glm::vec3 center(0, 0, 0);
	glm::vec3 up(0, 0, 1);
	glm::mat4 View = glm::lookAt(eye, center, up);

	glm::mat4 Model(1.0f);
	glm::mat4 MVP = Proj * View * Model;

	glUniformMatrix4fv(g_shaders.shader1.mvpLoc, 1, GL_FALSE, glm::value_ptr(MVP));



	glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, colorsBuffer);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indecesBuffer);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, nullptr);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}


static const GLfloat squareVertices[] = {
	-1, -1, 0,
	1, -1, 0,
	0, 1, 0
};

static const GLushort squareIndeces[] = {
	0, 1, 2
};

static const GLfloat squareColors[] = {
	1, 0, 0, 1,
	0, 1, 0, 1,
	0, 0, 1, 1
};

Mesh squareMesh;

void Primitives::Init(){
	squareMesh.Init();
	squareMesh.SetVertices(squareVertices, 9);
	squareMesh.SetIndeces(squareIndeces, 3);
	squareMesh.SetColors(squareColors, 16);
}

void Primitives::DrawSquare(){
	g_shaders.shader1.Use();

	squareMesh.Draw();
}

