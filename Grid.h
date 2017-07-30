
#pragma once

#include "Block.h"
#include "Mesh.h"

class Grid {

public:

	static constexpr int MaxWidth = 64;
	static constexpr int Width = 32;

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
