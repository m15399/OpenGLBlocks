
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

	std::vector<GLushort> boneIndeces;
	boneIndeces.reserve(nVertices * 4);

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

			GLushort boneIndex = i * w + j;
			boneIndeces.insert(boneIndeces.end(), 4, boneIndex);
			
			indeces.insert(indeces.end(), {
				(GLuint) (0 + vertexOffset), (GLuint) (1 + vertexOffset), (GLuint) (2 + vertexOffset),
				(GLuint) (0 + vertexOffset), (GLuint) (2 + vertexOffset), (GLuint) (3 + vertexOffset)
			});

			vertexOffset += 4;

		}
	}

	mesh.Set(&vertices[0], &colors[0], nVertices, &indeces[0], nTris);
	mesh.SetBoneIndeces(&boneIndeces[0], nVertices);
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

	std::vector<GLushort> boneIndeces;
	boneIndeces.reserve(nVertices * 4);
	
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

			GLushort boneIndex = i * w + j;
			boneIndeces.insert(boneIndeces.end(), 8, boneIndex);

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
	mesh.SetBoneIndeces(&boneIndeces[0], nVertices);
}

Mesh gridTopsMesh;
Mesh gridBottomsMesh;

void Grid::Init(){
	InitGridTopsMesh(gridTopsMesh, MaxWidth);
	InitGridBottomsMesh(gridBottomsMesh, MaxWidth);
}

#include <cmath>
#include "Time.h"

void Grid::Draw(){	
	int w = MaxWidth;
	int nSquares = w * w;
	int nVerticesTop = nSquares * 4;
	int nVerticesBottom = nSquares * 8;


	std::vector<GLubyte> colorsTop;
	colorsTop.reserve(nVerticesTop * 4);
	
	for(int i = 0; i < w; i++){
		for(int j = 0; j < w; j++){

			GLubyte r = 120;
			GLubyte g = 180;
			GLubyte b = 255;
			GLubyte a = 255;

			auto Brighten = [](GLubyte v){
				float brighten = 1.04f;
				return (GLubyte)(int)(std::ceil(std::min(brighten * v, 254.99f)));
			};

			auto SemiBrighten = [](GLubyte v){
				float semiBrighten = 1.02f;
				return (GLubyte)(int)(std::ceil(std::min(semiBrighten * v, 254.99f)));
			};

			colorsTop.insert(colorsTop.end(), {
				Brighten(r), Brighten(g), Brighten(b), a,
				r, g, b, a,
				r, g, b, a,
				SemiBrighten(r), SemiBrighten(g), SemiBrighten(b), a,
			});
		}
	}
	gridTopsMesh.SetColors(&colorsTop[0], nVerticesTop * 4);


	std::vector<GLubyte> colorsBottom;
	colorsBottom.reserve(nVerticesBottom * 4);

	for(int i = 0; i < w; i++){
		for(int j = 0; j < w; j++){

			GLubyte r = 120;
			GLubyte g = 180;
			GLubyte b = 250;

			colorsBottom.insert(colorsBottom.end(), {
				r, g, b, 255,
				r, g, b, 255,
				r, g, b, 255,
				r, g, b, 255,
				r, g, b, 0,
				r, g, b, 0,
				r, g, b, 0,
				r, g, b, 0,
			});
		}
	}
	gridBottomsMesh.SetColors(&colorsBottom[0], nVerticesBottom * 4);


	std::vector<GLfloat> vOffsets;
	vOffsets.reserve(nSquares);

	for(int i = 0; i < w; i++){
		for(int j = 0; j < w; j++){
			vOffsets.push_back((GLfloat)(std::sin((g_time.time % 1000000) / 1000.f + i/10.f + j/4.f) * 1.0f));
		}
	}


	Shader& shader = g_shaders.blockTop;
	shader.Use();
	glUniform4fv(shader.vOffsetsLoc, nSquares / 4, &vOffsets[0]);
	gridTopsMesh.Draw(g_shaders.blockTop);
	// glUniform4fv(shader.vOffsetsLoc, nSquares / 4, &vOffsets[0]);
	gridBottomsMesh.Draw(g_shaders.blockTop);
}

