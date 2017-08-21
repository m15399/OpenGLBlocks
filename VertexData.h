
#pragma once

#include <vector>

#include "SDL.h"
#include "Mesh.h"

class VertexData {
public:

	// TODO only works for most basic format right now

	std::vector<GLfloat> vertices;

	void PushVertex(GLfloat x, GLfloat y, GLfloat z);

	void SendToMesh(Mesh& mesh);
};