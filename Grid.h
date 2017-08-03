
#pragma once

#include "Block.h"
#include "Mesh.h"

class Grid {

public:

	static constexpr int MaxWidth = 256;
	static constexpr int Width = 64;

	static constexpr int nSquares = Width * Width;

	static constexpr int nVerticesTop = nSquares * 4;
	static constexpr int nTrisTop = nSquares * 2;
	
	static constexpr int nVerticesBottom = nSquares * 8;
	static constexpr int nTrisBottom = nSquares * 4;

	GLfloat verticesTop[nVerticesTop * 6] = {0};
	GLubyte colorsTop[nVerticesTop * 4] = {0};
	GLuint indecesTop[nTrisTop * 3] = {0};

	GLfloat verticesBottom[nVerticesBottom * 6] = {0};
	GLubyte colorsBottom[nVerticesBottom * 4] = {0};
	GLuint indecesBottom[nTrisBottom * 3] = {0};

	Mesh gridTopsMesh;
	Mesh gridBottomsMesh;

	Block blocks[MaxWidth * MaxWidth];

	float viewOffsetX = Width/2;
	float viewOffsetY = Width/2;

	void Init();
	Block* GetBlock(int x, int y);
	void Update();
	void UpdateMeshes(int chunk, int numChunks);
	void PushMeshes();
	void Draw();

};

extern Grid g_grid;
