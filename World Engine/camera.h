#pragma once
#include "transform.h"

class Camera
{
public:
	Transform transform;
	float fov;
	float zNear;
	float zFar;
};

