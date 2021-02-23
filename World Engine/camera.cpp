#include "pch.h"
#include "camera.h"

glm::mat4 Camera::GetProjection(float width, float height)
{
	return glm::perspective(glm::radians(fov),
		width / height,
		zNear,
		zFar);
}

glm::mat4 Camera::GetView()
{
	return glm::inverse(glm::translate(glm::mat4(1.0f), glm::vec3(transform.position.x, transform.position.y, -transform.position.z)) *
		glm::toMat4(glm::quat(glm::vec3(
			glm::radians(transform.rotation.x),
			glm::radians(-transform.rotation.y),
			glm::radians(transform.rotation.z)))));
}
