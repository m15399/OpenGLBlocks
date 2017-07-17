
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "Mesh.h"
#include "Camera.h"
#include "Shader.h"

glm::mat4 modelMatrix;


void Mesh::Init(){
	glGenBuffers(1, &verticesBuffer);
	glGenBuffers(1, &colorsBuffer);
	glGenBuffers(1, &vOffsetsBuffer);
	glGenBuffers(1, &indecesBuffer);
}

void Mesh::CopyVOffsetsBuffer(Mesh& other){
	glDeleteBuffers(1, &vOffsetsBuffer);
	vOffsetsBuffer = other.vOffsetsBuffer;
	borrowingVOffsets = true;
}

// Count is vertices.length - not number of vertices
//
void Mesh::SetVertices(const GLfloat* vertices, int count){
	glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
}

void Mesh::SetColors(const GLubyte* colors, int count){
	glBindBuffer(GL_ARRAY_BUFFER, colorsBuffer);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLubyte), colors, GL_DYNAMIC_DRAW);
}

void Mesh::SetVOffsets(const GLfloat* offsets, int count){
	glBindBuffer(GL_ARRAY_BUFFER, vOffsetsBuffer);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), offsets, GL_DYNAMIC_DRAW);
}

// TODO combine with SetVertices - calculate normals?
void Mesh::SetIndeces(const GLuint* indeces, int count){
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indecesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), indeces, GL_STATIC_DRAW);
	numIndeces = (GLsizei) count;
}

void Mesh::Set(const GLfloat* vertices, const GLubyte* colors, int numVertices,
			const GLuint* indeces, int numTris){
	SetVertices(vertices, numVertices * 3);
	SetColors(colors, numVertices * 4);
	SetIndeces(indeces, numTris * 3);
}

void Mesh::Draw(Shader& shader, const glm::mat4& modelMatrix, const glm::vec4& colorTint){

	shader.Use();

	glm::mat4 MVP = g_camera.GetViewProjMatrix() * modelMatrix;

	glUniformMatrix4fv(shader.mvpLoc, 1, GL_FALSE, glm::value_ptr(MVP));
	glUniform4fv(shader.colorTintLoc, 1, glm::value_ptr(colorTint));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indecesBuffer);


	glEnableVertexAttribArray(shader.positionAttrib);
	glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer);
	glVertexAttribPointer(shader.positionAttrib, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glEnableVertexAttribArray(shader.colorAttrib);
	glBindBuffer(GL_ARRAY_BUFFER, colorsBuffer);
	glVertexAttribPointer(shader.colorAttrib, 4, GL_UNSIGNED_BYTE, GL_FALSE, 0, nullptr);

	if(shader.vOffsetAttrib != -1){
		glEnableVertexAttribArray(shader.vOffsetAttrib);
		glBindBuffer(GL_ARRAY_BUFFER, vOffsetsBuffer);
		glVertexAttribPointer(shader.vOffsetAttrib, 1, GL_FLOAT, GL_FALSE, 0, nullptr);
	}

	// TODO can go back to ushort when not debugging large grids
	glDrawElements(GL_TRIANGLES, numIndeces, GL_UNSIGNED_INT, nullptr);

	glDisableVertexAttribArray(shader.colorAttrib);
	glDisableVertexAttribArray(shader.positionAttrib);

	if(shader.vOffsetAttrib != -1){
		glDisableVertexAttribArray(shader.vOffsetAttrib);
	}

}
