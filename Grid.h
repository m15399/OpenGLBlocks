
#pragma once

#include "Block.h"
#include "Mesh.h"

class Grid {

public:

	static constexpr int MaxWidth = 32;

	Block blocks[MaxWidth * MaxWidth];

	Mesh gridTopsMesh;
	Mesh gridBottomsMesh;

	void Init();
	void Draw();

	void UpdateTopMesh();
	void UpdateBottomMesh();
};

extern Grid g_grid;
