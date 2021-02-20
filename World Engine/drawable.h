#pragma once
#include "component.h"
#include "mesh.h"

class Drawable : public Component
{
public:
	Mesh mesh;
	Drawable(Mesh mesh);
	int Type() { return (int)ComponentType::Drawable; }
};

