
#pragma once

#include "Mesh.h"

class Primitives {
public:
	void Init();

	Mesh cube;
	Mesh square;
};

extern Primitives g_primitives;
