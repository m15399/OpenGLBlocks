
#pragma once

#include "Block.h"

class Grid {

public:

	static constexpr int MaxWidth = 32;

	Block blocks[MaxWidth * MaxWidth];

	void Init();
	void Draw();
};

extern Grid g_grid;
