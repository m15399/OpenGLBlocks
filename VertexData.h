
#pragma once

#include "SDL.h"

class VertexData {
public:

	// TODO only works for most basic format right now

	std::vector<GLfloat> vertices;
	std::vector<GLubyte> colors;

	void PushVertex(GLfloat x, GLfloat y, GLfloat z);
	void PushVertex(GLfloat x, GLfloat y, GLfloat z, GLfloat u, GLfloat v);
	void PushColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a);

	void SendToMesh(Mesh& mesh);
};