
#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

class Block {
public:

	glm::vec3 position;
	glm::vec4 topColor = glm::vec4(1.0f);
	glm::vec4 bottomColor = glm::vec4(1.0f);

	void SetPosition(const glm::vec3& pos);
	void SetTopColor(const glm::vec4& color);
	void SetBottomColor(const glm::vec4& color);
	void Draw();

};
