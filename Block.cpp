
#include "Block.h"
#include "Primitives.h"
#include "Shader.h"

#include <glm/gtc/matrix_transform.hpp>


void Block::SetPosition(const glm::vec3& pos){
	position = pos;
}

void Block::SetTopColor(const glm::vec4& color){
	topColor = color;
}

void Block::SetBottomColor(const glm::vec4& color){
	bottomColor = color;
}

void Block::Draw(){

	// float brighten = 1.04f;
	// float semiBrighten = 1.02f;

	// GLubyte top1[] = {
	// 	(GLubyte) (topColor.r * 255),
	// 	(GLubyte) (topColor.g * 255),
	// 	(GLubyte) (topColor.b * 255),
	// 	(GLubyte) (topColor.a * 255)
	// };

	// GLubyte top2[] = {
	// 	(GLubyte) (topColor.r * brighten * 255),
	// 	(GLubyte) (topColor.g * brighten * 255),
	// 	(GLubyte) (topColor.b * brighten * 255),
	// 	(GLubyte) (topColor.a * 255)
	// };

	// GLubyte top3[] = {
	// 	(GLubyte) (topColor.r * semiBrighten * 255),
	// 	(GLubyte) (topColor.g * semiBrighten * 255),
	// 	(GLubyte) (topColor.b * semiBrighten * 255),
	// 	(GLubyte) (topColor.a * 255)
	// };

	// GLubyte squareColors[] = {
	// 	top2[0], top2[1], top2[2], top2[3],
	// 	top1[0], top1[1], top1[2], top1[3],
	// 	top1[0], top1[1], top1[2], top1[3],
	// 	top3[0], top3[1], top3[2], top3[3],
	// };

	// g_primitives.square.SetColors(squareColors, 4 * 4);

	glm::mat4 modelMatrix(1.0f);
	modelMatrix = glm::translate(modelMatrix, position);

	Shader& shader = g_shaders.shader1;

	// TODO draw top and bot with seperate methods (draw all tops, then all bottoms)
	// TODO use private meshes instead of Primitive's ones

	g_primitives.square.Draw(shader, modelMatrix);
	// g_primitives.tube.Draw(shader, modelMatrix, bottomColor);
}
