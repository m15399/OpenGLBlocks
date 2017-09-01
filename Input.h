
#pragma once

#include "SDL.h"

class Input {

	static constexpr int KeyArraySize = 512;

	bool keysPressed[KeyArraySize] = {false};
	bool keysDown[KeyArraySize] = {false};


public:

	void Init();

	bool KeyPressed(SDL_Scancode scancode);
	bool KeyDown(SDL_Scancode scancode);

	void Update(); // Call this before updating keys
	void UpdateKey(SDL_KeyboardEvent& e);
};

extern Input g_input;
