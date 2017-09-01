
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
	verticesLen = count;
}

void Mesh::SetColors(const GLubyte* colors, int count){
	glBindBuffer(GL_ARRAY_BUFFER, a_colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLubyte), colors, GL_DYNAMIC_DRAW);
}

void Mesh::SetBoneIndeces(const GLushort* indeces, int count){
	glBindBuffer(GL_ARRAY_BUFFER, a_boneIndexBuffer);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLushort), indeces, GL_STATIC_DRAW);	
}

// TODO combine with SetVertices - to calculate normals?
// TOTO Or CalculateNormals is a separate step
void Mesh::SetIndeces(const GLuint* indeces, int count){
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indecesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), indeces, GL_STATIC_DRAW);
	numIndeces = (GLsizei) count;
	usingIndeces = true;
}

void Mesh::Draw(Shader& shader, const glm::mat4& modelMatrix, const glm::vec4& colorTint, Texture* texture){
	shader.Use();
	shader.EnableAttribs();

	glm::mat4 MVP = g_camera.GetViewProjMatrix() * modelMatrix;

	glUniformMatrix4fv(shader.mvpLoc, 1, GL_FALSE, glm::value_ptr(MVP));
	glUniform4fv(shader.colorTintLoc, 1, glm::value_ptr(colorTint));
	if(texture){
		texture->Use();
		glUniform1i(shader.texLoc, texture->boundUnit);
	}

	// Figure out what the shader expects
	//
	bool usesInlineNormalBuffer = shader.a_normalLoc != -1;
	bool usesInlineUvBuffer = shader.a_uvLoc != -1;
	bool usesSeparateColorBuffer = shader.a_colorLoc != -1;
	bool usesSeparateBoneIndexBuffer = shader.a_boneIndexLoc != -1;

	// Calculate sizes, offsets
	// Always have x, y, z
	//
	GLsizei currSize = 3 * sizeof(GL_FLOAT);

	uintptr_t inlineNormalOffset = currSize;
	if(usesInlineNormalBuffer)
		currSize += 3 * sizeof(GL_FLOAT);
	uintptr_t inlineUvOffset = currSize;
	if(usesInlineUvBuffer)
		currSize += 2 * sizeof(GL_FLOAT);

	GLsizei vertexStride = currSize;

	// Bind all the things
	//
	if(usingIndeces){
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indecesBuffer);
	}

	glBindBuffer(GL_ARRAY_BUFFER, a_positionBuffer);
	glVertexAttribPointer(shader.a_positionLoc, 3, GL_FLOAT, GL_FALSE, vertexStride, nullptr);

	if(usesInlineNormalBuffer){
		glVertexAttribPointer(shader.a_normalLoc, 3, GL_FLOAT, GL_FALSE, vertexStride, (void*) inlineNormalOffset);
	}

	if(usesInlineUvBuffer){
		glVertexAttribPointer(shader.a_uvLoc, 2, GL_FLOAT, GL_FALSE, vertexStride, (void*) inlineUvOffset);
	}

	if(usesSeparateColorBuffer){
		glBindBuffer(GL_ARRAY_BUFFER, a_colorBuffer);
		glVertexAttribPointer(shader.a_colorLoc, 4, GL_UNSIGNED_BYTE, GL_FALSE, 0, nullptr);
	}

	if(usesSeparateBoneIndexBuffer){
		glBindBuffer(GL_ARRAY_BUFFER, a_boneIndexBuffer);
		glVertexAttribPointer(shader.a_boneIndexLoc, 1, GL_UNSIGNED_SHORT, GL_FALSE, 0, nullptr);
	}

	// Draw
	//
	if(usingIndeces){
		// TODO can go back to ushort when not debugging large grids
		glDrawElements(GL_TRIANGLES, numIndeces, GL_UNSIGNED_INT, nullptr);
	} else {
		// TODO support more than just triangles
		glDrawArrays(GL_TRIANGLES, 0, verticesLen);
	}

	shader.DisableAttribs();
}
