
#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Camera {

	bool dirtyMatrix = true;
	glm::mat4 viewMatrix;
	glm::mat4 projMatrix;
	glm::mat4 viewProjMatrix;

public:

	glm::vec3 eye, center, up;

	void Init();

	void CenterOn(const glm::vec3 &point, float distance);

	glm::mat4 GetViewProjMatrix();

};

extern Camera g_camera;