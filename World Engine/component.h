#pragma once
#include "entity.h"

enum class ComponentType : int {
	Unknown,
	Transform,
	Drawable
};

class Component
{
public:
	Entity* entity;
	void SetEntity(Entity* entity);
	virtual int Type() { return (int)ComponentType::Unknown; }
};