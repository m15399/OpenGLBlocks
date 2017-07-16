
#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera g_camera;

void Camera::Init(){
	CenterOn(glm::vec3(0, 0, 0), 10);
}

void Camera::CenterOn(const glm::vec3 &point, float distance){
	eye = glm::vec3(-distance, -distance, distance);
	center = point;
	up = glm::vec3(0, 0, 1);
	dirtyMatrix = true;
}

glm::mat4 Camera::GetViewProjMatrix(){
	if(dirtyMatrix){
		viewMatrix = glm::lookAt(eye, center, up);
		// TODO use correct aspect ratio
		projMatrix = glm::perspective(glm::radians(45.0f), 1.33f, .1f, 10000.f);
		viewProjMatrix = projMatrix * viewMatrix;
		dirtyMatrix = false;
	}
	return viewProjMatrix;
}
