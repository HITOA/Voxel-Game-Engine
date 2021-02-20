#pragma once
#include "vector3.h"
#include "component.h"

class Transform : public Component
{
public:
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
	Transform();
	int Type() { return (int)ComponentType::Transform; }
};

