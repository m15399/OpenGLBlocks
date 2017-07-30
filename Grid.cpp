
#include <iostream>
#include <cmath>

#include "Grid.h"
#include "Mesh.h"
#include "Utils.h"
#include "Time.h"

Grid g_grid;

void Grid::Init(){
	gridTopsMesh.Init();
	gridBottomsMesh.Init();

	for(int i = 0; i < MaxWidth; i++){
		for(int j = 0; j < MaxWidth; j++){
			Block& block = blocks[i * MaxWidth + j];
			block.Init(j, i);
		}
	}
}

void Grid::UpdateTopMesh(){
	constexpr int w = MaxWidth;
	constexpr int nSquares = w * w;
	constexpr int nVertices = nSquares * 4;
	constexpr int nTris = nSquares * 2;

	GLfloat vertices[nVertices * 3];
	GLubyte colors[nVertices * 4];
	GLuint indeces[nTris * 3];

	GLuint vertexOffset = 0;
	GLuint indexOffset = 0;

	auto Brighten = [](GLubyte v){
		float brighten = 1.04f;
		return (GLubyte)(int)(std::ceil(std::min(brighten * v, 254.99f)));
	};

	auto SemiBrighten = [](GLubyte v){
		float semiBrighten = 1.02f;
		return (GLubyte)(int)(std::ceil(std::min(semiBrighten * v, 254.99f)));
	};

	for(int i = 0; i < w; i++){
		for(int j = 0; j < w; j++){
			Block& block = blocks[i * MaxWidth + j];

			int xo = j - w/2;
			int yo = i - w/2;

			GLfloat zo = block.z;

			GLubyte r = block.topColor[0];
			GLubyte g = block.topColor[1];
			GLubyte b = block.topColor[2];
			GLubyte a = block.topColor[3];

			vertices[(vertexOffset + 0) * 3 + 0] = .5f + xo;
			vertices[(vertexOffset + 0) * 3 + 1] = .5f + yo;
			vertices[(vertexOffset + 0) * 3 + 2] = zo;

			vertices[(vertexOffset + 1) * 3 + 0] = -.5f + xo;
			vertices[(vertexOffset + 1) * 3 + 1] = .5f + yo;
			vertices[(vertexOffset + 1) * 3 + 2] = zo;

			vertices[(vertexOffset + 2) * 3 + 0] = -.5f + xo;
			vertices[(vertexOffset + 2) * 3 + 1] = -.5f + yo;
			vertices[(vertexOffset + 2) * 3 + 2] = zo;

			vertices[(vertexOffset + 3) * 3 + 0] = .5f + xo;
			vertices[(vertexOffset + 3) * 3 + 1] = -.5f + yo;
			vertices[(vertexOffset + 3) * 3 + 2] = zo;

			colors[(vertexOffset + 0) * 4 + 0] = (GLubyte) Brighten(r);
			colors[(vertexOffset + 0) * 4 + 1] = (GLubyte) Brighten(g);
			colors[(vertexOffset + 0) * 4 + 2] = (GLubyte) Brighten(b);
			colors[(vertexOffset + 0) * 4 + 3] = (GLubyte) a;

			colors[(vertexOffset + 1) * 4 + 0] = (GLubyte) r;
			colors[(vertexOffset + 1) * 4 + 1] = (GLubyte) g;
			colors[(vertexOffset + 1) * 4 + 2] = (GLubyte) b;
			colors[(vertexOffset + 1) * 4 + 3] = (GLubyte) a;

			colors[(vertexOffset + 2) * 4 + 0] = (GLubyte) r;
			colors[(vertexOffset + 2) * 4 + 1] = (GLubyte) g;
			colors[(vertexOffset + 2) * 4 + 2] = (GLubyte) b;
			colors[(vertexOffset + 2) * 4 + 3] = (GLubyte) a;

			colors[(vertexOffset + 3) * 4 + 0] = (GLubyte) SemiBrighten(r);
			colors[(vertexOffset + 3) * 4 + 1] = (GLubyte) SemiBrighten(g);
			colors[(vertexOffset + 3) * 4 + 2] = (GLubyte) SemiBrighten(b);
			colors[(vertexOffset + 3) * 4 + 3] = (GLubyte) a;

			indeces[indexOffset + 0] = vertexOffset + 0;
			indeces[indexOffset + 1] = vertexOffset + 1;
			indeces[indexOffset + 2] = vertexOffset + 2;
			indeces[indexOffset + 3] = vertexOffset + 0;
			indeces[indexOffset + 4] = vertexOffset + 2;
			indeces[indexOffset + 5] = vertexOffset + 3;

			vertexOffset += 4;
			indexOffset += 6;
		}
	}

	gridTopsMesh.Set(&vertices[0], &colors[0], nVertices, &indeces[0], nTris);
}

void Grid::UpdateBottomMesh(){
	constexpr int w = MaxWidth;
	constexpr int nSquares = w * w;
	constexpr int nVertices = nSquares * 8;
	constexpr int nTris = nSquares * 8;

	GLfloat vertices[nVertices * 3];
	GLubyte colors[nVertices * 4];
	GLuint indeces[nTris * 3];

	GLuint vertexOffset = 0;
	GLuint indexOffset = 0;


	for(int i = 0; i < w; i++){
		for(int j = 0; j < w; j++){
			Block& block = blocks[i * MaxWidth + j];

			int xo = j - w/2;
			int yo = i - w/2;

			GLfloat zo = block.z;
		
			GLubyte r = block.bottomColor[0];
			GLubyte g = block.bottomColor[1];
			GLubyte b = block.bottomColor[2];
			GLubyte a = block.bottomColor[3];

			vertices[(vertexOffset + 0) * 3 + 0] = .5f + xo;
			vertices[(vertexOffset + 0) * 3 + 1] = .5f + yo;
			vertices[(vertexOffset + 0) * 3 + 2] = zo;

			vertices[(vertexOffset + 1) * 3 + 0] = -.5f + xo;
			vertices[(vertexOffset + 1) * 3 + 1] = .5f + yo;
			vertices[(vertexOffset + 1) * 3 + 2] = zo;

			vertices[(vertexOffset + 2) * 3 + 0] = -.5f + xo;
			vertices[(vertexOffset + 2) * 3 + 1] = -.5f + yo;
			vertices[(vertexOffset + 2) * 3 + 2] = zo;

			vertices[(vertexOffset + 3) * 3 + 0] = .5f + xo;
			vertices[(vertexOffset + 3) * 3 + 1] = -.5f + yo;
			vertices[(vertexOffset + 3) * 3 + 2] = zo;

			vertices[(vertexOffset + 4) * 3 + 0] = .5f + xo;
			vertices[(vertexOffset + 4) * 3 + 1] = .5f + yo;
			vertices[(vertexOffset + 4) * 3 + 2] = zo - 1;

			vertices[(vertexOffset + 5) * 3 + 0] = -.5f + xo;
			vertices[(vertexOffset + 5) * 3 + 1] = .5f + yo;
			vertices[(vertexOffset + 5) * 3 + 2] = zo - 1;

			vertices[(vertexOffset + 6) * 3 + 0] = -.5f + xo;
			vertices[(vertexOffset + 6) * 3 + 1] = -.5f + yo;
			vertices[(vertexOffset + 6) * 3 + 2] = zo - 1;

			vertices[(vertexOffset + 7) * 3 + 0] = .5f + xo;
			vertices[(vertexOffset + 7) * 3 + 1] = -.5f + yo;
			vertices[(vertexOffset + 7) * 3 + 2] = zo - 1;

			colors[(vertexOffset + 0) * 4 + 0] = (GLubyte) r;
			colors[(vertexOffset + 0) * 4 + 1] = (GLubyte) g;
			colors[(vertexOffset + 0) * 4 + 2] = (GLubyte) b;
			colors[(vertexOffset + 0) * 4 + 3] = (GLubyte) a;

			colors[(vertexOffset + 1) * 4 + 0] = (GLubyte) r;
			colors[(vertexOffset + 1) * 4 + 1] = (GLubyte) g;
			colors[(vertexOffset + 1) * 4 + 2] = (GLubyte) b;
			colors[(vertexOffset + 1) * 4 + 3] = (GLubyte) a;

			colors[(vertexOffset + 2) * 4 + 0] = (GLubyte) r;
			colors[(vertexOffset + 2) * 4 + 1] = (GLubyte) g;
			colors[(vertexOffset + 2) * 4 + 2] = (GLubyte) b;
			colors[(vertexOffset + 2) * 4 + 3] = (GLubyte) a;

			colors[(vertexOffset + 3) * 4 + 0] = (GLubyte) r;
			colors[(vertexOffset + 3) * 4 + 1] = (GLubyte) g;
			colors[(vertexOffset + 3) * 4 + 2] = (GLubyte) b;
			colors[(vertexOffset + 3) * 4 + 3] = (GLubyte) a;

			colors[(vertexOffset + 4) * 4 + 0] = (GLubyte) r;
			colors[(vertexOffset + 4) * 4 + 1] = (GLubyte) g;
			colors[(vertexOffset + 4) * 4 + 2] = (GLubyte) b;
			colors[(vertexOffset + 4) * 4 + 3] = (GLubyte) 0;

			colors[(vertexOffset + 5) * 4 + 0] = (GLubyte) r;
			colors[(vertexOffset + 5) * 4 + 1] = (GLubyte) g;
			colors[(vertexOffset + 5) * 4 + 2] = (GLubyte) b;
			colors[(vertexOffset + 5) * 4 + 3] = (GLubyte) 0;

			colors[(vertexOffset + 6) * 4 + 0] = (GLubyte) r;
			colors[(vertexOffset + 6) * 4 + 1] = (GLubyte) g;
			colors[(vertexOffset + 6) * 4 + 2] = (GLubyte) b;
			colors[(vertexOffset + 6) * 4 + 3] = (GLubyte) 0;

			colors[(vertexOffset + 7) * 4 + 0] = (GLubyte) r;
			colors[(vertexOffset + 7) * 4 + 1] = (GLubyte) g;
			colors[(vertexOffset + 7) * 4 + 2] = (GLubyte) b;
			colors[(vertexOffset + 7) * 4 + 3] = (GLubyte) 0;

			indeces[(indexOffset + 0) * 3 + 0] = vertexOffset + 0;
			indeces[(indexOffset + 0) * 3 + 1] = vertexOffset + 3;
			indeces[(indexOffset + 0) * 3 + 2] = vertexOffset + 7;

			indeces[(indexOffset + 1) * 3 + 0] = vertexOffset + 0;
			indeces[(indexOffset + 1) * 3 + 1] = vertexOffset + 7;
			indeces[(indexOffset + 1) * 3 + 2] = vertexOffset + 4;

			indeces[(indexOffset + 2) * 3 + 0] = vertexOffset + 0;
			indeces[(indexOffset + 2) * 3 + 1] = vertexOffset + 4;
			indeces[(indexOffset + 2) * 3 + 2] = vertexOffset + 5;

			indeces[(indexOffset + 3) * 3 + 0] = vertexOffset + 0;
			indeces[(indexOffset + 3) * 3 + 1] = vertexOffset + 5;
			indeces[(indexOffset + 3) * 3 + 2] = vertexOffset + 1;

			indeces[(indexOffset + 4) * 3 + 0] = vertexOffset + 6;
			indeces[(indexOffset + 4) * 3 + 1] = vertexOffset + 2;
			indeces[(indexOffset + 4) * 3 + 2] = vertexOffset + 1;

			indeces[(indexOffset + 5) * 3 + 0] = vertexOffset + 6;
			indeces[(indexOffset + 5) * 3 + 1] = vertexOffset + 1;
			indeces[(indexOffset + 5) * 3 + 2] = vertexOffset + 5;

			indeces[(indexOffset + 6) * 3 + 0] = vertexOffset + 6;
			indeces[(indexOffset + 6) * 3 + 1] = vertexOffset + 7;
			indeces[(indexOffset + 6) * 3 + 2] = vertexOffset + 3;

			indeces[(indexOffset + 7) * 3 + 0] = vertexOffset + 6;
			indeces[(indexOffset + 7) * 3 + 1] = vertexOffset + 3;
			indeces[(indexOffset + 7) * 3 + 2] = vertexOffset + 2;

			vertexOffset += 8;
			indexOffset += 8;
		}
	}

	gridBottomsMesh.Set(&vertices[0], &colors[0], nVertices, &indeces[0], nTris);
}

void Grid::Draw(){

	for(int i = 0; i < MaxWidth; i++){
		for (int j = 0; j < MaxWidth; j++){
			Block& block = blocks[i * MaxWidth + j];
			block.Update();
		}
	}

	UpdateTopMesh();
	gridTopsMesh.Draw(g_shaders.shader1);
	UpdateBottomMesh();
	gridBottomsMesh.Draw(g_shaders.shader1);
}

