
#pragma once

#include "SDL.h"

class Player {
public:

	float x = 0;
	float y = 0;

	void Update();
	void Draw();

};

extern Player g_player;
