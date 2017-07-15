
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Primitives.h"
#include "SDL.h"
#include "Shader.h"

Primitives g_primitives;

glm::mat4 modelMatrix;


class Mesh {

	GLuint verticesBuffer;
	GLuint indecesBuffer;
	GLsizei numIndeces;

public:
	
	void Init();	
	void SetVertices(const GLfloat* vertices, int count);
	void SetIndeces(const GLushort* indeces, int count);
	void Draw();

};

void Mesh::Init(){
	glGenBuffers(1, &verticesBuffer);
	glGenBuffers(1, &indecesBuffer);
}

// Count is vertices.length - not number of vertices
//
void Mesh::SetVertices(const GLfloat* vertices, int count){
	glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
}

// Count is indeces.length
//
void Mesh::SetIndeces(const GLushort* indeces, int count){
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indecesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), indeces, GL_STATIC_DRAW);
	numIndeces = (GLsizei) count;
}

void Mesh::Draw(){
	// TODO pass modelMatrix in
	modelMatrix = glm::rotate(modelMatrix, .01f, glm::vec3(0, 0, 1));

	// TODO move to Camera class
	glm::mat4 Proj = glm::perspective(glm::radians(45.0f), 1.33f, .1f, 1000.f);
	float d = 5;
	glm::vec3 eye(-d, -d, d);
	glm::vec3 center(0, 0, 0);
	glm::vec3 up(0, 0, 1);
	glm::mat4 View = glm::lookAt(eye, center, up);


	glm::mat4 MVP = Proj * View * modelMatrix;


	// TODO get the current shader's attrib positions
	Shader& currShader = g_shaders.shader1;

	glUniformMatrix4fv(currShader.mvpLoc, 1, GL_FALSE, glm::value_ptr(MVP));


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indecesBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GL_FLOAT), nullptr);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GL_FLOAT), (void*) (3 * sizeof(GL_FLOAT)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glDrawElements(GL_TRIANGLES, numIndeces, GL_UNSIGNED_SHORT, nullptr);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}


static const GLfloat cubeVertices[] = {
	.5f, .5f, .5f,  0, 1, 1, 1,
	-.5f, .5f, .5f,  1, 0, 1, 1,
	-.5f, -.5f, .5f,  1, 1, 0, 1,
	.5f, -.5f, .5f,  0, 0, 0, 1,
	.5f, .5f, -.5f,  1, 1, 1, 1,
	-.5f, .5f, -.5f,  1, 1, 1, 1,
	-.5f, -.5f, -.5f,  1, 1, 1, 1,
	.5f, -.5f, -.5f,  1, 1, 1, 1
};

static const GLushort cubeIndeces[] = {
	0, 1, 2,    0, 2, 3,
	0, 3, 7,    0, 7, 4,
	0, 4, 5,    0, 5, 1,
	6, 5, 4,    6, 4, 7,
	6, 2, 1,    6, 1, 5,
	6, 7, 3,    6, 3, 2
};


Mesh cubeMesh;

void Primitives::Init(){
	cubeMesh.Init();
	cubeMesh.SetVertices(cubeVertices, 7 * 8);
	cubeMesh.SetIndeces(cubeIndeces, 12 * 3);
}

void Primitives::DrawCube(){
	g_shaders.shader1.Use();

	cubeMesh.Draw();
}

