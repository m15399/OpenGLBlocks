
#include <vector>
#include <iostream>

#include "Grid.h"
#include "Mesh.h"
#include "Utils.h"

Grid g_grid;

void InitGridTopsMesh(Mesh& mesh, int w){
	mesh.Init();

	int nSquares = w * w;
	int nVertices = nSquares * 4;
	int nTris = nSquares * 2;

	std::vector<GLfloat> vertices;
	vertices.reserve(nVertices * 3);

	std::vector<GLubyte> colors;
	colors.reserve(nVertices * 4);

	std::vector<GLuint> indeces;
	indeces.reserve(nTris * 3);

	GLuint vertexOffset = 0;

	for(int i = 0; i < w; i++){
		for(int j = 0; j < w; j++){
			int xo = j - w/2;
			int yo = i - w/2;

			vertices.insert(vertices.end(), {
				.5f + xo, .5f + yo, 0,
				-.5f + xo, .5f + yo, 0,
				-.5f + xo, -.5f + yo, 0,
				.5f + xo, -.5f + yo, 0
			});

			colors.insert(colors.end(), {
				255, 255, 255, 255,
				255, 255, 255, 255,
				255, 255, 255, 255,
				255, 255, 255, 255
			});

			indeces.insert(indeces.end(), {
				(GLuint) (0 + vertexOffset), (GLuint) (1 + vertexOffset), (GLuint) (2 + vertexOffset),
				(GLuint) (0 + vertexOffset), (GLuint) (2 + vertexOffset), (GLuint) (3 + vertexOffset)
			});

			vertexOffset += 4;

		}
	}

	mesh.Set(&vertices[0], &colors[0], nVertices, &indeces[0], nTris);
}

void InitGridBottomsMesh(Mesh& mesh, int w){
	mesh.Init();

	int nSquares = w * w;
	int nVertices = nSquares * 8;
	int nTris = nSquares * 8;

	std::vector<GLfloat> vertices;
	vertices.reserve(nVertices * 3);

	std::vector<GLubyte> colors;
	colors.reserve(nVertices * 4);

	std::vector<GLfloat> vOffsets;
	vOffsets.reserve(nVertices);
	
	std::vector<GLuint> indeces;
	indeces.reserve(nTris * 3);

	GLuint vertexOffset = 0;

	for(int i = 0; i < w; i++){
		for(int j = 0; j < w; j++){
			int xo = j - w/2;
			int yo = i - w/2;

			vertices.insert(vertices.end(), {
				.5f + xo, .5f + yo, 0,
				-.5f + xo, .5f + yo, 0,
				-.5f + xo, -.5f + yo, 0,
				.5f + xo, -.5f + yo, 0,
				.5f + xo, .5f + yo, -1,
				-.5f + xo, .5f + yo, -1,
				-.5f + xo, -.5f + yo, -1,
				.5f + xo, -.5f + yo, -1
			});

			colors.insert(colors.end(), {
				255, 255, 255, 255,
				255, 255, 255, 255,
				255, 255, 255, 255,
				255, 255, 255, 255,
				255, 255, 255, 0,
				255, 255, 255, 0,
				255, 255, 255, 0,
				255, 255, 255, 0
			});

			float verticalOffset = 0;
			vOffsets.insert(vOffsets.end(), {
				verticalOffset, verticalOffset, verticalOffset, verticalOffset,
				verticalOffset, verticalOffset, verticalOffset, verticalOffset
			});

			indeces.insert(indeces.end(), {
				(GLuint) (0 + vertexOffset), (GLuint) (3 + vertexOffset), (GLuint) (7 + vertexOffset),
				(GLuint) (0 + vertexOffset), (GLuint) (7 + vertexOffset), (GLuint) (4 + vertexOffset),
				(GLuint) (0 + vertexOffset), (GLuint) (4 + vertexOffset), (GLuint) (5 + vertexOffset),
				(GLuint) (0 + vertexOffset), (GLuint) (5 + vertexOffset), (GLuint) (1 + vertexOffset),
				(GLuint) (6 + vertexOffset), (GLuint) (2 + vertexOffset), (GLuint) (1 + vertexOffset),
				(GLuint) (6 + vertexOffset), (GLuint) (1 + vertexOffset), (GLuint) (5 + vertexOffset),
				(GLuint) (6 + vertexOffset), (GLuint) (7 + vertexOffset), (GLuint) (3 + vertexOffset),
				(GLuint) (6 + vertexOffset), (GLuint) (3 + vertexOffset), (GLuint) (2 + vertexOffset),
			});

			vertexOffset += 8;

		}
	}

	mesh.Set(&vertices[0], &colors[0], nVertices, &indeces[0], nTris);
	mesh.SetVOffsets(&vOffsets[0], nVertices);
}

Mesh gridTopsMesh;
Mesh gridBottomsMesh;

void Grid::Init(){
	InitGridTopsMesh(gridTopsMesh, MaxWidth);
	InitGridBottomsMesh(gridBottomsMesh, MaxWidth);

	gridTopsMesh.CopyVOffsetsBuffer(gridBottomsMesh);
}

void Grid::Draw(){	
	int w = MaxWidth;
	int nSquares = w * w;
	int nVerticesTop = nSquares * 4;
	int nVerticesBottom = nSquares * 8;

	std::vector<GLubyte> colorsTop;
	colorsTop.reserve(nVerticesTop * 4);

	std::vector<GLfloat> vOffsetsBottom;
	vOffsetsBottom.reserve(nVerticesBottom);
	
	for(int i = 0; i < w; i++){
		for(int j = 0; j < w; j++){

			// TODO send topcolor and botcolor in seperate buffers
			colorsTop.insert(colorsTop.end(), {
				0, 0, 255, 255,
				255, 0, 255, 255,
				255, 255, 0, 255,
				255, 255, 255, 255,
			});

			float verticalOffset = Random(0.f, 1.f);
			vOffsetsBottom.insert(vOffsetsBottom.end(), 8, verticalOffset);
		}
	}
	gridTopsMesh.SetColors(&colorsTop[0], nVerticesTop * 4);
	gridBottomsMesh.SetVOffsets(&vOffsetsBottom[0], nVerticesBottom); // topMesh borrows this

	gridTopsMesh.Draw(g_shaders.blockTop);
	gridBottomsMesh.Draw(g_shaders.blockTop);
}

