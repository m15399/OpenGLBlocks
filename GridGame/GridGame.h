
#pragma once

#include "../SDL.h"
#include "Block.h"
#include "Grid.h"
#include "Player.h"


class GridGame : public Game {
public:

	float defaultCameraDistance = 1.f * 20.f;

	virtual void Init();
	virtual void Update();
	virtual void Draw();
};

extern GridGame g_gridGame;
