#pragma once
#include "component.h"
#include "mesh.h"
#include "material.h"

class Drawable : public Component
{
public:
	Mesh mesh;
	Material* material;
	Drawable(Mesh mesh);
	int Type() { return (int)ComponentType::Drawable; }
};

