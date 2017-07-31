
#pragma once

#include "Block.h"
#include "Mesh.h"

class Grid {

public:

	static constexpr int MaxWidth = 256;
	static constexpr int Width = 64;

	Block blocks[MaxWidth * MaxWidth];

	Mesh gridTopsMesh;
	Mesh gridBottomsMesh;

	float viewOffsetX = Width/2;
	float viewOffsetY = Width/2;

	void Init();
	void Update();
	void Draw();

	void UpdateMeshes();
};

extern Grid g_grid;
