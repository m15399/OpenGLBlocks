
Game* g_game = nullptr;


// Temporary location...


#include <vector>
#include "SDL.h"
#include "VertexData.h"
#include "Color.h"
#include "Utils.h"


void PushSquare(VertexData& v, float x, float y, float size){
	float s2 = size/2;
	float x1 = x - s2;
	float y1 = y - s2;
	float x2 = x + s2;
	float y2 = y + s2;

	// GLubyte r = (GLubyte) Random(0, 255);
	// GLubyte g = (GLubyte) Random(0, 255);
	// GLubyte b = (GLubyte) Random(0, 255);
	GLubyte r = 255;
	GLubyte g = 255;
	GLubyte b = 255;

	v.PushVertex(x1, y1, 0, 0, 0);
	v.PushVertex(x2, y1, 0, 1, 0);
	v.PushVertex(x1, y2, 0, 0, 1);
	v.PushVertex(x1, y2, 0, 0, 1);
	v.PushVertex(x2, y1, 0, 1, 0);
	v.PushVertex(x2, y2, 0, 1, 1);

	v.PushColor(r, g, b, 255);
	v.PushColor(r, g, b, 255);
	v.PushColor(r, g, b, 255);
	v.PushColor(r, g, b, 255);
	v.PushColor(r, g, b, 255);
	v.PushColor(r, g, b, 255);
}

Texture tex;

void Game::Init(){
	tex.Init("pup.png");
}

void Game::Update(){}


void Game::Draw(){

	Mesh m;
	VertexData v;
	float s = .5f;
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			PushSquare(v, i * s, j * s, s);
		}
	}
	v.SendToMesh(m);
	m.Draw(g_shaders.basic_color_tex, glm::mat4(1.0f), Color(255, 255, 255, 255).ToVec4(), &tex);
}
