
#pragma once

#include "Game.h"

class GridGame : public Game {
public:

	float defaultCameraDistance = 1.f * 20.f;

	virtual void Init();
	virtual void Update();
	virtual void Draw();
};

extern GridGame g_gridGame;
