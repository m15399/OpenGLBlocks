
void VertexData::PushVertex(GLfloat x, GLfloat y, GLfloat z){
	vertices.push_back(x);
	vertices.push_back(y);
	vertices.push_back(z);
}

void VertexData::PushVertex(GLfloat x, GLfloat y, GLfloat z, GLfloat u, GLfloat v){
	vertices.push_back(x);
	vertices.push_back(y);
	vertices.push_back(z);
	vertices.push_back(u);
	vertices.push_back(v);
}

void VertexData::PushColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a){
	colors.push_back(r);
	colors.push_back(g);
	colors.push_back(b);
	colors.push_back(a);
}

void VertexData::SendToMesh(Mesh& mesh){
	mesh.SetVertices(&vertices[0], vertices.size());

	if(colors.size() > 0){
		mesh.SetColors(&colors[0], colors.size());
	}
}

void VertexData::Clear(){
	vertices.clear();
	colors.clear();
}
