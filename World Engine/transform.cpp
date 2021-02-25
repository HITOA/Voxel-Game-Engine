#include "pch.h"
#include "transform.h"

Transform::Transform()
{
	scale.x = 1;
	scale.y = 1;
	scale.z = 1;
}

void Transform::Translate(Vector3 translation, Space space)
{
	if (space == Space::World) {
		position.x += translation.x;
		position.y += translation.y;
		position.z += translation.z;
		return;
	}

	glm::quat rot = glm::quat(glm::vec3(
		glm::radians(rotation.x),
		glm::radians(rotation.y),
		glm::radians(rotation.z)));

	glm::vec3 result = rot * glm::vec3(translation.x, translation.y, translation.z);

	position.x += result.x;
	position.y += -result.y;
	position.z += result.z;
}

glm::mat4 Transform::GetModel()
{
	return glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, position.z)) *
		glm::toMat4(glm::quat(glm::vec3(
			glm::radians(rotation.x),
			glm::radians(rotation.y),
			glm::radians(rotation.z)))) *
		glm::scale(glm::vec3(scale.x, scale.y, scale.z));
}
