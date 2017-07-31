
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

void Grid::UpdateMeshes(int chunk, int numChunks){
	constexpr int maxW = MaxWidth;
	constexpr int w = Width;

	int rowsPerChunk = w / numChunks;
	int rowOffset = chunk * rowsPerChunk;

	int vox = std::floor(viewOffsetX);
	int voy = std::floor(viewOffsetY);

	int squaresPerChunk = nSquares / numChunks;
	int verticesTopPerChunk = 4 * squaresPerChunk;
	int indecesTopPerChunk = 6 * squaresPerChunk;
	int verticesBottomPerChunk = 8 * squaresPerChunk;
	int indecesBottomPerChunk = 8 * squaresPerChunk;

	// Top Mesh

	GLuint vertexOffset = verticesTopPerChunk * chunk;
	GLuint indexOffset = indecesTopPerChunk * chunk;

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

			verticesTop[(vertexOffset + 0) * 3 + 0] = .5f + xo;
			verticesTop[(vertexOffset + 0) * 3 + 1] = .5f + yo;
			verticesTop[(vertexOffset + 0) * 3 + 2] = zo;

			verticesTop[(vertexOffset + 1) * 3 + 0] = -.5f + xo;
			verticesTop[(vertexOffset + 1) * 3 + 1] = .5f + yo;
			verticesTop[(vertexOffset + 1) * 3 + 2] = zo;

			verticesTop[(vertexOffset + 2) * 3 + 0] = -.5f + xo;
			verticesTop[(vertexOffset + 2) * 3 + 1] = -.5f + yo;
			verticesTop[(vertexOffset + 2) * 3 + 2] = zo;

			verticesTop[(vertexOffset + 3) * 3 + 0] = .5f + xo;
			verticesTop[(vertexOffset + 3) * 3 + 1] = -.5f + yo;
			verticesTop[(vertexOffset + 3) * 3 + 2] = zo;

			colorsTop[(vertexOffset + 0) * 4 + 0] = (GLubyte) Brighten(r);
			colorsTop[(vertexOffset + 0) * 4 + 1] = (GLubyte) Brighten(g);
			colorsTop[(vertexOffset + 0) * 4 + 2] = (GLubyte) Brighten(b);
			colorsTop[(vertexOffset + 0) * 4 + 3] = (GLubyte) a;

			colorsTop[(vertexOffset + 1) * 4 + 0] = (GLubyte) r;
			colorsTop[(vertexOffset + 1) * 4 + 1] = (GLubyte) g;
			colorsTop[(vertexOffset + 1) * 4 + 2] = (GLubyte) b;
			colorsTop[(vertexOffset + 1) * 4 + 3] = (GLubyte) a;

			colorsTop[(vertexOffset + 2) * 4 + 0] = (GLubyte) r;
			colorsTop[(vertexOffset + 2) * 4 + 1] = (GLubyte) g;
			colorsTop[(vertexOffset + 2) * 4 + 2] = (GLubyte) b;
			colorsTop[(vertexOffset + 2) * 4 + 3] = (GLubyte) a;

			colorsTop[(vertexOffset + 3) * 4 + 0] = (GLubyte) SemiBrighten(r);
			colorsTop[(vertexOffset + 3) * 4 + 1] = (GLubyte) SemiBrighten(g);
			colorsTop[(vertexOffset + 3) * 4 + 2] = (GLubyte) SemiBrighten(b);
			colorsTop[(vertexOffset + 3) * 4 + 3] = (GLubyte) a;

			// TODO these are always the same
			indecesTop[indexOffset + 0] = vertexOffset + 0;
			indecesTop[indexOffset + 1] = vertexOffset + 1;
			indecesTop[indexOffset + 2] = vertexOffset + 2;
			indecesTop[indexOffset + 3] = vertexOffset + 0;
			indecesTop[indexOffset + 4] = vertexOffset + 2;
			indecesTop[indexOffset + 5] = vertexOffset + 3;

			vertexOffset += 4;
			indexOffset += 6;
		}
	}

	// Bottom mesh

	vertexOffset = verticesBottomPerChunk * chunk;
	indexOffset = indecesBottomPerChunk * chunk;

	// TODO chop unseen parts of grid
	for(int i = rowOffset; i < rowOffset + rowsPerChunk; i++){
		for(int j = 0; j < w; j++){

			GLubyte r = 0;
			GLubyte g = 0;
			GLubyte b = 0;
			GLubyte a = 0;
			GLubyte bottomA = 0;

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
				bottomA = a;

				zo = block.z;
			}

			float height = 10;

			verticesBottom[(vertexOffset + 0) * 3 + 0] = .5f + xo;
			verticesBottom[(vertexOffset + 0) * 3 + 1] = .5f + yo;
			verticesBottom[(vertexOffset + 0) * 3 + 2] = zo;

			verticesBottom[(vertexOffset + 1) * 3 + 0] = -.5f + xo;
			verticesBottom[(vertexOffset + 1) * 3 + 1] = .5f + yo;
			verticesBottom[(vertexOffset + 1) * 3 + 2] = zo;

			verticesBottom[(vertexOffset + 2) * 3 + 0] = -.5f + xo;
			verticesBottom[(vertexOffset + 2) * 3 + 1] = -.5f + yo;
			verticesBottom[(vertexOffset + 2) * 3 + 2] = zo;

			verticesBottom[(vertexOffset + 3) * 3 + 0] = .5f + xo;
			verticesBottom[(vertexOffset + 3) * 3 + 1] = -.5f + yo;
			verticesBottom[(vertexOffset + 3) * 3 + 2] = zo;

			verticesBottom[(vertexOffset + 4) * 3 + 0] = .5f + xo;
			verticesBottom[(vertexOffset + 4) * 3 + 1] = .5f + yo;
			verticesBottom[(vertexOffset + 4) * 3 + 2] = zo - height;

			verticesBottom[(vertexOffset + 5) * 3 + 0] = -.5f + xo;
			verticesBottom[(vertexOffset + 5) * 3 + 1] = .5f + yo;
			verticesBottom[(vertexOffset + 5) * 3 + 2] = zo - height;

			verticesBottom[(vertexOffset + 6) * 3 + 0] = -.5f + xo;
			verticesBottom[(vertexOffset + 6) * 3 + 1] = -.5f + yo;
			verticesBottom[(vertexOffset + 6) * 3 + 2] = zo - height;

			verticesBottom[(vertexOffset + 7) * 3 + 0] = .5f + xo;
			verticesBottom[(vertexOffset + 7) * 3 + 1] = -.5f + yo;
			verticesBottom[(vertexOffset + 7) * 3 + 2] = zo - height;

			colorsBottom[(vertexOffset + 0) * 4 + 0] = (GLubyte) r;
			colorsBottom[(vertexOffset + 0) * 4 + 1] = (GLubyte) g;
			colorsBottom[(vertexOffset + 0) * 4 + 2] = (GLubyte) b;
			colorsBottom[(vertexOffset + 0) * 4 + 3] = (GLubyte) a;

			colorsBottom[(vertexOffset + 1) * 4 + 0] = (GLubyte) r;
			colorsBottom[(vertexOffset + 1) * 4 + 1] = (GLubyte) g;
			colorsBottom[(vertexOffset + 1) * 4 + 2] = (GLubyte) b;
			colorsBottom[(vertexOffset + 1) * 4 + 3] = (GLubyte) a;

			colorsBottom[(vertexOffset + 2) * 4 + 0] = (GLubyte) r;
			colorsBottom[(vertexOffset + 2) * 4 + 1] = (GLubyte) g;
			colorsBottom[(vertexOffset + 2) * 4 + 2] = (GLubyte) b;
			colorsBottom[(vertexOffset + 2) * 4 + 3] = (GLubyte) a;

			colorsBottom[(vertexOffset + 3) * 4 + 0] = (GLubyte) r;
			colorsBottom[(vertexOffset + 3) * 4 + 1] = (GLubyte) g;
			colorsBottom[(vertexOffset + 3) * 4 + 2] = (GLubyte) b;
			colorsBottom[(vertexOffset + 3) * 4 + 3] = (GLubyte) a;

			colorsBottom[(vertexOffset + 4) * 4 + 0] = (GLubyte) r;
			colorsBottom[(vertexOffset + 4) * 4 + 1] = (GLubyte) g;
			colorsBottom[(vertexOffset + 4) * 4 + 2] = (GLubyte) b;
			colorsBottom[(vertexOffset + 4) * 4 + 3] = (GLubyte) bottomA;

			colorsBottom[(vertexOffset + 5) * 4 + 0] = (GLubyte) r;
			colorsBottom[(vertexOffset + 5) * 4 + 1] = (GLubyte) g;
			colorsBottom[(vertexOffset + 5) * 4 + 2] = (GLubyte) b;
			colorsBottom[(vertexOffset + 5) * 4 + 3] = (GLubyte) bottomA;

			colorsBottom[(vertexOffset + 6) * 4 + 0] = (GLubyte) r;
			colorsBottom[(vertexOffset + 6) * 4 + 1] = (GLubyte) g;
			colorsBottom[(vertexOffset + 6) * 4 + 2] = (GLubyte) b;
			colorsBottom[(vertexOffset + 6) * 4 + 3] = (GLubyte) bottomA;

			colorsBottom[(vertexOffset + 7) * 4 + 0] = (GLubyte) r;
			colorsBottom[(vertexOffset + 7) * 4 + 1] = (GLubyte) g;
			colorsBottom[(vertexOffset + 7) * 4 + 2] = (GLubyte) b;
			colorsBottom[(vertexOffset + 7) * 4 + 3] = (GLubyte) bottomA;

			indecesBottom[(indexOffset + 0) * 3 + 0] = vertexOffset + 0;
			indecesBottom[(indexOffset + 0) * 3 + 1] = vertexOffset + 3;
			indecesBottom[(indexOffset + 0) * 3 + 2] = vertexOffset + 7;

			indecesBottom[(indexOffset + 1) * 3 + 0] = vertexOffset + 0;
			indecesBottom[(indexOffset + 1) * 3 + 1] = vertexOffset + 7;
			indecesBottom[(indexOffset + 1) * 3 + 2] = vertexOffset + 4;

			indecesBottom[(indexOffset + 2) * 3 + 0] = vertexOffset + 0;
			indecesBottom[(indexOffset + 2) * 3 + 1] = vertexOffset + 4;
			indecesBottom[(indexOffset + 2) * 3 + 2] = vertexOffset + 5;

			indecesBottom[(indexOffset + 3) * 3 + 0] = vertexOffset + 0;
			indecesBottom[(indexOffset + 3) * 3 + 1] = vertexOffset + 5;
			indecesBottom[(indexOffset + 3) * 3 + 2] = vertexOffset + 1;

			indecesBottom[(indexOffset + 4) * 3 + 0] = vertexOffset + 6;
			indecesBottom[(indexOffset + 4) * 3 + 1] = vertexOffset + 2;
			indecesBottom[(indexOffset + 4) * 3 + 2] = vertexOffset + 1;

			indecesBottom[(indexOffset + 5) * 3 + 0] = vertexOffset + 6;
			indecesBottom[(indexOffset + 5) * 3 + 1] = vertexOffset + 1;
			indecesBottom[(indexOffset + 5) * 3 + 2] = vertexOffset + 5;

			indecesBottom[(indexOffset + 6) * 3 + 0] = vertexOffset + 6;
			indecesBottom[(indexOffset + 6) * 3 + 1] = vertexOffset + 7;
			indecesBottom[(indexOffset + 6) * 3 + 2] = vertexOffset + 3;

			indecesBottom[(indexOffset + 7) * 3 + 0] = vertexOffset + 6;
			indecesBottom[(indexOffset + 7) * 3 + 1] = vertexOffset + 3;
			indecesBottom[(indexOffset + 7) * 3 + 2] = vertexOffset + 2;

			vertexOffset += 8;
			indexOffset += 8;
		}
	}
}

void Grid::PushMeshes(){
	gridTopsMesh.Set(&verticesTop[0], &colorsTop[0], nVerticesTop, &indecesTop[0], nTrisTop);
	gridBottomsMesh.Set(&verticesBottom[0], &colorsBottom[0], nVerticesBottom, &indecesBottom[0], nTrisBottom);
}

void Grid::Update(){
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

