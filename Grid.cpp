
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

void Grid::UpdateMeshes(){
	constexpr int maxW = MaxWidth;
	constexpr int w = Width;
	constexpr int nSquares = w * w;

	int vox = std::floor(viewOffsetX);
	int voy = std::floor(viewOffsetY);

	int i0 = std::max(voy - w/2, 0);
	int i1 = std::min(voy + w/2, maxW);

	int j0 = std::max(vox - w/2, 0);
	int j1 = std::min(vox + w/2, maxW);

	auto Falloff = [this, w](int a, float x, float y)
	{
		// constexpr float falloffSpacing = 3.5f;
		// float dx = std::abs(x + 1 - viewOffsetX);
		// float dy = std::abs(y + 1 - viewOffsetY);
		// float d = std::max(dx, dy);
		// float dEdge = (w/2 - d);


		// float ratio = dEdge / falloffSpacing;

		// float alpha = std::min(a * ratio, 255.1f);
		
		// return (int) std::floor(alpha);
		return a;
	};

	// Top Mesh
	{
		constexpr int nVertices = nSquares * 4;
		constexpr int nTris = nSquares * 2;

		// TODO don't have to clear the WHOLE array, just the parts we don't update
		GLfloat vertices[nVertices * 3] = {0};
		GLubyte colors[nVertices * 4] = {0};
		GLuint indeces[nTris * 3] = {0};

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

		// TODO flip the representation so we iterate in order of data
		for(int i = i1 - 1; i >= i0; i--){
			for(int j = j1 - 1; j >= j0; j--){
				Block& block = blocks[i * MaxWidth + j];

				int xo = j;
				int yo = i;

				GLfloat zo = block.z;

				GLubyte r = block.topColor[0];
				GLubyte g = block.topColor[1];
				GLubyte b = block.topColor[2];
				GLubyte a = Falloff(block.topColor[3], xo, yo);

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

	// Bottom Mesh
	{
		constexpr int nVertices = nSquares * 8;
		constexpr int nTris = nSquares * 8;

		// TODO don't have to clear the WHOLE array, just the parts we don't update
		GLfloat vertices[nVertices * 3] = {0};
		GLubyte colors[nVertices * 4] = {0};
		GLuint indeces[nTris * 3] = {0};

		GLuint vertexOffset = 0;
		GLuint indexOffset = 0;

		// TODO chop unseen parts of grid
		for(int i = i1 - 1; i >= i0; i--){
			for(int j = j1 - 1; j >= j0; j--){
				Block& block = blocks[i * MaxWidth + j];

				int xo = j;
				int yo = i;

				GLfloat zo = block.z;
			
				GLubyte r = block.bottomColor[0];
				GLubyte g = block.bottomColor[1];
				GLubyte b = block.bottomColor[2];
				GLubyte a = Falloff(block.bottomColor[3], xo, yo);

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
	UpdateMeshes();
	gridBottomsMesh.Draw(g_shaders.shader1);
	gridTopsMesh.Draw(g_shaders.shader1);
}

