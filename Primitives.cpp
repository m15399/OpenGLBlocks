
#include "Primitives.h"
#include "SDL.h"
#include "Mesh.h"

Primitives g_primitives;

GLfloat tubeVertices[] = {
	.5f, .5f, .5f,
	-.5f, .5f, .5f,
	-.5f, -.5f, .5f,
	.5f, -.5f, .5f,
	.5f, .5f, -.5f,
	-.5f, .5f, -.5f,
	-.5f, -.5f, -.5f,
	.5f, -.5f, -.5f
};

GLubyte tubeColors[] = {
	255, 255, 255, 255,
	255, 255, 255, 255,
	255, 255, 255, 255,
	255, 255, 255, 255,
	255, 255, 255, 0,
	255, 255, 255, 0,
	255, 255, 255, 0,
	255, 255, 255, 0
};

GLuint tubeIndeces[] = {
	0, 3, 7,    0, 7, 4,
	0, 4, 5,    0, 5, 1,
	6, 2, 1,    6, 1, 5,
	6, 7, 3,    6, 3, 2
};


GLfloat squareVertices[] = {
	.5f, .5f, .5f,
	-.5f, .5f, .5f,
	-.5f, -.5f, .5f,
	.5f, -.5f, .5f,
};

GLubyte squareColors[] = {
	0, 255, 255, 255,
	255, 0, 255, 255,
	255, 255, 0, 255,
	255, 255, 255, 255,
};

GLuint squareIndeces[] = {
	0, 1, 2,    0, 2, 3,
};

static const GLfloat cubeVertices[] = {
	.5f, .5f, .5f,
	-.5f, .5f, .5f,
	-.5f, -.5f, .5f,
	.5f, -.5f, .5f,
	.5f, .5f, -.5f,
	-.5f, .5f, -.5f,
	-.5f, -.5f, -.5f,
	.5f, -.5f, -.5f
};

static const GLubyte cubeColors[] = {
	255, 255, 0, 255,
	0, 255, 255, 255,
	255, 0, 255, 255,
	255, 0, 255, 255,
	255, 255, 0, 255,
	255, 255, 255, 255,
	255, 255, 255, 255,
	255, 255, 255, 255
};

static const GLuint cubeIndeces[] = {
	0, 1, 2,    0, 2, 3,
	0, 3, 7,    0, 7, 4,
	0, 4, 5,    0, 5, 1,
	6, 5, 4,    6, 4, 7,
	6, 2, 1,    6, 1, 5,
	6, 7, 3,    6, 3, 2
};


void Primitives::Init(){
	cube.Init();
	cube.Set(cubeVertices, cubeColors, 8, cubeIndeces, 12);
	tube.Init();
	tube.Set(tubeVertices, tubeColors, 8, tubeIndeces, 8);
	square.Init();
	square.Set(squareVertices, squareColors, 4, squareIndeces, 2);
}


