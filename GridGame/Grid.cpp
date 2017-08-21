
#include <iostream>
#include <cmath>

#include "Grid.h"
#include "../Mesh.h"
#include "../Utils.h"
#include "../Time.h"
#include "../Input.h"
#include "Player.h"

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

Block* Grid::GetBlock(int x, int y){
	if(y >= 0 && y < MaxWidth && x >= 0 && x < MaxWidth)
		return &blocks[y * MaxWidth + x];
	else
		return nullptr;
}


inline void PushVertex(GLfloat* vertices, GLubyte* colors, int* currVertex,
	float x, float y, float z, float nx, float ny, float nz,
	GLubyte r, GLubyte g, GLubyte b, GLubyte a){

	int vertexOffset = *currVertex;

	vertices[vertexOffset * 6 + 0] = x;
	vertices[vertexOffset * 6 + 1] = y;
	vertices[vertexOffset * 6 + 2] = z;
	vertices[vertexOffset * 6 + 3] = nx;
	vertices[vertexOffset * 6 + 4] = ny;
	vertices[vertexOffset * 6 + 5] = nz;

	colors[vertexOffset * 4 + 0] = r;
	colors[vertexOffset * 4 + 1] = g;
	colors[vertexOffset * 4 + 2] = b;
	colors[vertexOffset * 4 + 3] = a;

	(*currVertex)++;
}

inline void PushTri(GLuint* indeces, int* currTri, int vertexOffset,
	GLuint a, GLuint b, GLuint c){

	int triOffset = *currTri;

	indeces[triOffset * 3 + 0] = vertexOffset + a;
	indeces[triOffset * 3 + 1] = vertexOffset + b;
	indeces[triOffset * 3 + 2] = vertexOffset + c;

	(*currTri)++;
}


void Grid::UpdateMeshes(int chunk, int numChunks){
	constexpr int maxW = MaxWidth;
	constexpr int w = Width;

	int rowsPerChunk = w / numChunks;
	int rowOffset = chunk * rowsPerChunk;

	int vox = std::floor(viewOffsetX);
	int voy = std::floor(viewOffsetY);

	int squaresPerChunk = nSquares / numChunks;
	int verticesTopPerChunk = 4 * squaresPerChunk;
	int trisTopPerChunk = 2 * squaresPerChunk;
	int verticesBottomPerChunk = 8 * squaresPerChunk;
	int trisBottomPerChunk = 4 * squaresPerChunk;

	// Top Mesh

	GLuint vertexOffset = verticesTopPerChunk * chunk;
	GLuint triOffset = trisTopPerChunk * chunk;

	#if 1

	// TODO flip the representation so we iterate in order of data
	for(int i = rowOffset; i < rowOffset + rowsPerChunk; i++){
		for(int j = 0; j < w; j++){

			Color baseColor(0, 0, 0, 0);

			GLfloat zo = -10000;

			int blockRow = voy - w/2 + i;
			int blockColumn = vox - w/2 + j;

			int yo = blockRow;
			int xo = blockColumn;

			if(blockRow >= 0 && blockRow < maxW && blockColumn >= 0 && blockColumn < maxW){
				Block& block = blocks[blockRow * MaxWidth + blockColumn];

				baseColor = block.topColor;
				zo = block.z;
			}

			Color brightened = baseColor;
			brightened.Brighten(1.04f);

			Color semiBrightened = baseColor;
			semiBrightened.Brighten(1.02f);

			int currVertex = vertexOffset;
			int currTri = triOffset;

			#define PV(x, y, z, nx, ny, nz, color) \
				PushVertex(verticesTop, colorsTop, &currVertex, \
					x, y, z, nx, ny, nz, \
					color.r, color.g, color.b, color.a)

			#define PT(a, b, c) \
				PushTri(indecesTop, &currTri, vertexOffset, \
					a, b, c)

			PV(.5f + xo, .5f + yo, zo,     0, 0, 1, brightened);
			PV(-.5f + xo, .5f + yo, zo,    0, 0, 1, baseColor);
			PV(-.5f + xo, -.5f + yo, zo,   0, 0, 1, baseColor);
			PV(.5f + xo, -.5f + yo, zo,    0, 0, 1, semiBrightened);
			
			// TODO these never change so just push them once
			PT(0, 1, 2);
			PT(0, 2, 3);

			#undef PT
			#undef PV

			vertexOffset = currVertex;
			triOffset = currTri;
		}
	}
	#endif

	// Bottom mesh
	#if 1

	vertexOffset = verticesBottomPerChunk * chunk;
	triOffset = trisBottomPerChunk * chunk;

	// TODO chop unseen parts of grid
	for(int i = rowOffset; i < rowOffset + rowsPerChunk; i++){
		for(int j = 0; j < w; j++){

			Color baseColor;

			GLfloat zo = -10000;

			int blockRow = voy - w/2 + i;
			int blockColumn = vox - w/2 + j;

			int yo = blockRow;
			int xo = blockColumn;

			if(blockRow >= 0 && blockRow < maxW && blockColumn >= 0 && blockColumn < maxW){
				Block& block = blocks[blockRow * MaxWidth + blockColumn];

				baseColor = block.bottomColor;
				zo = block.z;
			}

			float height = 10;

			int currVertex = vertexOffset;
			int currTri = triOffset;

			#define PV(x, y, z, nx, ny, nz) \
				PushVertex(verticesBottom, colorsBottom, &currVertex, \
					x, y, z, nx, ny, nz, \
					baseColor.r, baseColor.g, baseColor.b, baseColor.a)

			#define PT(a, b, c) \
				PushTri(indecesBottom, &currTri, vertexOffset, \
					a, b, c)

			PV(.5f + xo, -.5f + yo, zo,              0, -1, 0);
			PV(-.5f + xo, -.5f + yo, zo,             0, -1, 0);
			PV(-.5f + xo, -.5f + yo, -height + zo,   0, -1, 0);
			PV(.5f + xo, -.5f + yo, -height + zo,    0, -1, 0);

			PV(-.5f + xo, -.5f + yo, zo,             -1, 0, 0);
			PV(-.5f + xo, .5f + yo, zo,              -1, 0, 0);
			PV(-.5f + xo, .5f + yo, -height + zo,    -1, 0, 0);
			PV(-.5f + xo, -.5f + yo, -height + zo,   -1, 0, 0);
			
			PT(0, 1, 2);
			PT(0, 2, 3);
			PT(4, 5, 6);
			PT(4, 6, 7);

			#undef PT
			#undef PV

			vertexOffset = currVertex;
			triOffset = currTri;
		}
	}
	#endif
}

void Grid::PushMeshes(){
	gridTopsMesh.SetVertices(&verticesTop[0], nVerticesTop * 6);
	gridTopsMesh.SetColors(&colorsTop[0], nVerticesTop * 4);
	gridTopsMesh.SetIndeces(&indecesTop[0], nTrisTop * 3);

	gridBottomsMesh.SetVertices(&verticesBottom[0], nVerticesBottom * 6);
	gridBottomsMesh.SetColors(&colorsBottom[0], nVerticesBottom * 4);
	gridBottomsMesh.SetIndeces(&indecesBottom[0], nTrisBottom * 3);

}

void Grid::Update(){
	viewOffsetX = g_player.x;
	viewOffsetY = g_player.y;

	// TODO update in parallel
	for(int i = 0; i < MaxWidth; i++){
		for (int j = 0; j < MaxWidth; j++){
			Block& block = blocks[i * MaxWidth + j];
			block.UpdateHeights();
		}
	}

	// This must be done after all the heights are worked out
	for(int i = 0; i < MaxWidth; i++){
		for (int j = 0; j < MaxWidth; j++){
			Block& block = blocks[i * MaxWidth + j];
			block.UpdateLighting();
		}
	}
}

void Grid::Draw(){
	gridBottomsMesh.Draw(g_shaders.shader1);
	gridTopsMesh.Draw(g_shaders.shader1);
}

