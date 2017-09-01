
#pragma once

#include "SDL.h"

class Texture {
public:

	static Texture* currTexture;

	GLuint textureId;

	int width = 0;
	int height = 0;
	int numChannels = 0;

	int boundUnit = -1;

	void Init(const char* filename);
	void Use();
	void Unuse();
};
