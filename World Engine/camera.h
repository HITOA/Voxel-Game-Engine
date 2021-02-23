#pragma once
#include "transform.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/transform.hpp>
#include <gtc/quaternion.hpp>
#include <gtx/quaternion.hpp>

class Camera
{
public:
	Transform transform;
	float fov;
	float zNear;
	float zFar;
	glm::mat4 GetProjection(float width, float height);
	glm::mat4 GetView();
};

