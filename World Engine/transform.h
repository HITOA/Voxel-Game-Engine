#pragma once
#include "vector3.h"
#include "component.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/transform.hpp>
#include <gtc/quaternion.hpp>
#include <gtx/quaternion.hpp>

enum class Space {
	World,
	Self
};

class Transform : public Component
{
public:
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
	Transform();
	int Type() { return (int)ComponentType::Transform; }
	void Translate(Vector3 translation, Space space = Space::Self);
	glm::mat4 GetModel();
};

