
#include "VertexData.h"

void VertexData::PushVertex(GLfloat x, GLfloat y, GLfloat z){
	vertices.push_back(x);
	vertices.push_back(y);
	vertices.push_back(z);
}

void VertexData::SendToMesh(Mesh& mesh){
	mesh.SetVertices(&vertices[0], vertices.size());
}
