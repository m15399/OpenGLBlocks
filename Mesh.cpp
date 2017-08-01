
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "Mesh.h"
#include "Camera.h"
#include "Shader.h"

glm::mat4 modelMatrix;


void Mesh::Init(){
	#define GEN_SHADER_BUFFER(name) \
		glGenBuffers(1, &name##Buffer);

	SHADER_ATTRIB_LIST(GEN_SHADER_BUFFER);

	glGenBuffers(1, &indecesBuffer);
}

// Count is vertices.length - not number of vertices
//
void Mesh::SetVertices(const GLfloat* vertices, int count){
	glBindBuffer(GL_ARRAY_BUFFER, a_positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
}

void Mesh::SetColors(const GLubyte* colors, int count){
	glBindBuffer(GL_ARRAY_BUFFER, a_colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLubyte), colors, GL_DYNAMIC_DRAW);
}

void Mesh::SetBoneIndeces(const GLushort* indeces, int count){
	glBindBuffer(GL_ARRAY_BUFFER, a_boneIndexBuffer);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLushort), indeces, GL_STATIC_DRAW);	
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


	glEnableVertexAttribArray(shader.a_positionLoc);
	glEnableVertexAttribArray(shader.a_normalLoc);
	glBindBuffer(GL_ARRAY_BUFFER, a_positionBuffer);
	glVertexAttribPointer(shader.a_positionLoc, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), nullptr);
	glVertexAttribPointer(shader.a_normalLoc, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), 
		(void*) (3 * sizeof(GL_FLOAT)));

	glEnableVertexAttribArray(shader.a_colorLoc);
	glBindBuffer(GL_ARRAY_BUFFER, a_colorBuffer);
	glVertexAttribPointer(shader.a_colorLoc, 4, GL_UNSIGNED_BYTE, GL_FALSE, 0, nullptr);

	if(shader.a_boneIndexLoc != -1){
		glEnableVertexAttribArray(shader.a_boneIndexLoc);
		glBindBuffer(GL_ARRAY_BUFFER, a_boneIndexBuffer);

		glVertexAttribPointer(shader.a_boneIndexLoc, 1, GL_UNSIGNED_SHORT, GL_FALSE, 0, nullptr);
	}

	// TODO can go back to ushort when not debugging large grids
	glDrawElements(GL_TRIANGLES, numIndeces, GL_UNSIGNED_INT, nullptr);

	glDisableVertexAttribArray(shader.a_colorLoc);
	glDisableVertexAttribArray(shader.a_positionLoc);
	glDisableVertexAttribArray(shader.a_normalLoc);

	if(shader.a_boneIndexLoc != -1){
		glDisableVertexAttribArray(shader.a_boneIndexLoc);
	}

}
