
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "Player.h"
#include "Input.h"
#include "Time.h"
#include "Primitives.h"
#include "Shader.h"
#include "Grid.h"

Player g_player;

void Player::Update(){
	float speed = 4.f * dt();

	glm::vec2 moveDir;

	if(g_input.KeyDown(SDL_SCANCODE_LEFT) || g_input.KeyDown(SDL_SCANCODE_A)){
		moveDir += glm::vec2(-1, 1);
	}
	if(g_input.KeyDown(SDL_SCANCODE_RIGHT) || g_input.KeyDown(SDL_SCANCODE_D)){
		moveDir += glm::vec2(1, -1);
	}
	if(g_input.KeyDown(SDL_SCANCODE_UP) || g_input.KeyDown(SDL_SCANCODE_W)){
		moveDir += glm::vec2(1, 1);
	}
	if(g_input.KeyDown(SDL_SCANCODE_DOWN) || g_input.KeyDown(SDL_SCANCODE_S)){
		moveDir += glm::vec2(-1, -1);
	}

	glm::vec2 moveAmount{0, 0};

	if(glm::length(moveDir) > 0.1f){
		moveAmount = glm::normalize(moveDir) * speed;
	}

	x += moveAmount.x;
	y += moveAmount.y;
}

void Player::Draw(){

	float oz = 0;

	Block* block = g_grid.GetBlock((int) x, (int) y);
	if(block){
		oz = block->z;
	}

	oz += .5f;

	glm::mat4 transform;
	transform = glm::translate(transform, glm::vec3(x, y, oz));

	g_primitives.cube.Draw(g_shaders.shader1, transform);
}
