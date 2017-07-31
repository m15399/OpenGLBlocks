
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
	if(g_input.KeyDown(SDL_SCANCODE_I))
		cameraDistance *= (1 - cameraSpeed * dt());
	if(g_input.KeyDown(SDL_SCANCODE_K))
		cameraDistance *= (1 + cameraSpeed * dt());
	if(g_input.KeyPressed(SDL_SCANCODE_O))
		cameraDistance = defaultCameraDistance;
	
	float x = g_grid.viewOffsetX;
	float y = g_grid.viewOffsetY;
	CenterOn(glm::vec3(x, y, 0), cameraDistance);


}

void Camera::CenterOn(const glm::vec3 &point, float distance){
	eye = glm::vec3(point.x - distance, point.y - distance, point.z + distance * 1.25f);
	center = point;
	up = glm::vec3(0, 0, 1);
	dirtyMatrix = true;
}

glm::mat4 Camera::GetViewProjMatrix(){
	if(dirtyMatrix){
		viewMatrix = glm::lookAt(eye, center, up);

		float aspect = (float) g_window.width / g_window.height;
		projMatrix = glm::perspective(glm::radians(30.0f), aspect, 1.0f, 100.f);

		viewProjMatrix = projMatrix * viewMatrix;
		dirtyMatrix = false;
	}
	return viewProjMatrix;
}
