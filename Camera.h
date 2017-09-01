
#pragma once

#include "SDL.h"

class Camera {

	bool dirtyMatrix = true;
	glm::mat4 viewMatrix;
	glm::mat4 projMatrix;
	glm::mat4 viewProjMatrix;

public:

	enum class Mode {
		Targetted,
		TopDown
	};

	Mode mode = Mode::Targetted;

	float defaultCameraDistance = 10;
	float cameraDistance = defaultCameraDistance;

	float rotationX = 0;
	float offsetY = 0;

	glm::vec3 eye, center, up;

	void Init();

	void Update();

	void CenterOn(const glm::vec3 &point, float distance = 0);

	glm::mat4 GetViewProjMatrix();

};

extern Camera g_camera;
