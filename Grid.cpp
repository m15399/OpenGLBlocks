
#include <iostream>
#include <cmath>

#include "Grid.h"
#include "Mesh.h"
#include "Utils.h"
#include "Time.h"
#include "Input.h"

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

	auto Brighten = [](GLubyte v){
		float brighten = 1.04f;
		return (GLubyte)(int)(std::ceil(std::min(brighten * v, 254.99f)));
	};

	auto SemiBrighten = [](GLubyte v){
		float semiBrighten = 1.02f;
		return (GLubyte)(int)(std::ceil(std::min(semiBrighten * v, 254.99f)));
	};

	// TODO flip the representation so we iterate in order of data
	for(int i = rowOffset; i < rowOffset + rowsPerChunk; i++){
		for(int j = 0; j < w; j++){

			GLubyte r = 0;
			GLubyte g = 0;
			GLubyte b = 0;
			GLubyte a = 0;

			GLfloat zo = -10000;

			int blockRow = voy - w/2 + i;
			int blockColumn = vox - w/2 + j;

			int yo = blockRow;
			int xo = blockColumn;

			if(blockRow >= 0 && blockRow < maxW && blockColumn >= 0 && blockColumn < maxW){
				Block& block = blocks[blockRow * MaxWidth + blockColumn];

				r = block.topColor[0];
				g = block.topColor[1];
				b = block.topColor[2];
				a = block.topColor[3];

				zo = block.z;
			}

			int currVertex = vertexOffset;
			int currTri = triOffset;

			#define PV(x, y, z, nx, ny, nz, r, g, b) \
				PushVertex(verticesTop, colorsTop, &currVertex, \
					x, y, z, nx, ny, nz, \
					r, g, b, a)

			#define PT(a, b, c) \
				PushTri(indecesTop, &currTri, vertexOffset, \
					a, b, c)

			PV(.5f + xo, .5f + yo, zo,     0, 0, 1, Brighten(r), Brighten(g), Brighten(b));
			PV(-.5f + xo, .5f + yo, zo,    0, 0, 1, r, g, b);
			PV(-.5f + xo, -.5f + yo, zo,   0, 0, 1, r, g, b);
			PV(.5f + xo, -.5f + yo, zo,    0, 0, 1, SemiBrighten(r), SemiBrighten(g), SemiBrighten(b));
			
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

			GLubyte r = 0;
			GLubyte g = 0;
			GLubyte b = 0;
			GLubyte a = 0;

			GLfloat zo = -10000;

			int blockRow = voy - w/2 + i;
			int blockColumn = vox - w/2 + j;

			int yo = blockRow;
			int xo = blockColumn;

			if(blockRow >= 0 && blockRow < maxW && blockColumn >= 0 && blockColumn < maxW){
				Block& block = blocks[blockRow * MaxWidth + blockColumn];

				r = block.bottomColor[0];
				g = block.bottomColor[1];
				b = block.bottomColor[2];
				a = block.bottomColor[3];

				zo = block.z;
			}

			float height = 10;

			int currVertex = vertexOffset;
			int currTri = triOffset;

			#define PV(x, y, z, nx, ny, nz) \
				PushVertex(verticesBottom, colorsBottom, &currVertex, \
					x, y, z, nx, ny, nz, \
					r, g, b, a)

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
	gridTopsMesh.Set(&verticesTop[0], &colorsTop[0], nVerticesTop, &indecesTop[0], nTrisTop);
	gridBottomsMesh.Set(&verticesBottom[0], &colorsBottom[0], nVerticesBottom, &indecesBottom[0], nTrisBottom);
}

void Grid::Update(){
	// TODO update in parallel
	for(int i = 0; i < MaxWidth; i++){
		for (int j = 0; j < MaxWidth; j++){
			Block& block = blocks[i * MaxWidth + j];
			block.Update();
		}
	}

	float speed = 4.f * dt();
	if(g_input.KeyDown(SDL_SCANCODE_LEFT)){
		viewOffsetX -= speed;
	}
	if(g_input.KeyDown(SDL_SCANCODE_RIGHT)){
		viewOffsetX += speed;
	}
	if(g_input.KeyDown(SDL_SCANCODE_UP)){
		viewOffsetY += speed;
	}
	if(g_input.KeyDown(SDL_SCANCODE_DOWN)){
		viewOffsetY -= speed;
	}
}

void Grid::Draw(){
	gridBottomsMesh.Draw(g_shaders.shader1);
	gridTopsMesh.Draw(g_shaders.shader1);
}

