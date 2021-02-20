#include "pch.h"
#include "mesh.h"

Mesh::Mesh()
{
	glGenBuffers(1, &vbo);
}

void Mesh::Update()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verticies.size(), verticies.data(), GL_DYNAMIC_DRAW);
}
