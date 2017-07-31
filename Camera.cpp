
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "Camera.h"
#include "Window.h"
#include "Input.h"
#include "Time.h"
#include "Grid.h"

Camera g_camera;

void Camera::Init(){
	CenterOn(glm::vec3(0, 0, 0), 10);
}

void Camera::Update(){
	float cameraSpeed = .5f;
	float rotSpeed = .8f;
	float voSpeed = .8f;

	if(g_input.KeyDown(SDL_SCANCODE_I))
		cameraDistance *= (1 - cameraSpeed * dt());
	if(g_input.KeyDown(SDL_SCANCODE_K))
		cameraDistance *= (1 + cameraSpeed * dt());
	if(g_input.KeyDown(SDL_SCANCODE_J))
		rotationX -= (rotSpeed * dt());
	if(g_input.KeyDown(SDL_SCANCODE_L))
		rotationX += (rotSpeed * dt());
	if(g_input.KeyDown(SDL_SCANCODE_O))
		offsetY += (voSpeed * dt());
	if(g_input.KeyDown(SDL_SCANCODE_U))
		offsetY -= (voSpeed * dt());

	if(g_input.KeyPressed(SDL_SCANCODE_0)){
		cameraDistance = defaultCameraDistance;
		offsetY = 0;
		rotationX = 0;
	}
	
	float x = g_grid.viewOffsetX;
	float y = g_grid.viewOffsetY;
	CenterOn(glm::vec3(x, y, 0), cameraDistance);
}

void Camera::CenterOn(const glm::vec3 &point, float distance){
	eye = glm::vec3(-distance, -distance, distance * (1.25f + offsetY) );
	eye = glm::rotate(eye, rotationX, glm::vec3(0, 0, 1));
	eye += point;

	center = point;
	
	up = glm::vec3(0, 0, 1);
	
	dirtyMatrix = true;
}

glm::mat4 Camera::GetViewProjMatrix(){
	if(dirtyMatrix){
		viewMatrix = glm::lookAt(eye, center, up);

		float aspect = (float) g_window.width / g_window.height;
		projMatrix = glm::perspective(glm::radians(30.0f), aspect, 1.0f, 500.f);

		viewProjMatrix = projMatrix * viewMatrix;
		dirtyMatrix = false;
	}
	return viewProjMatrix;
}
