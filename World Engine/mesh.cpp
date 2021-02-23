#include "pch.h"
#include "mesh.h"

Mesh::Mesh()
{
	glGenBuffers(1, &meshVBO);
	glGenBuffers(1, &indicesVBO);
}

void Mesh::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, meshVBO);

	GLintptr p = 0;

	glVertexAttribPointer(0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)p);
	p += GetVerticiesBufferSize();

	glVertexAttribPointer(1,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)p);
	p += GetColorsBufferSize();

	glVertexAttribPointer(2,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)p);
	p += GetNormalsBufferSize();

	glVertexAttribPointer(3,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)p);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesVBO);
}

void Mesh::AddVertex(Vector3 vertex)
{
	vertices.push_back(vertex.x);
	vertices.push_back(vertex.y);
	vertices.push_back(vertex.z);
}

void Mesh::AddColor(Vector3 color)
{
	colors.push_back(color.x);
	colors.push_back(color.y);
	colors.push_back(color.z);
}

void Mesh::AddNormals(Vector3 normal)
{
	normals.push_back(normal.x);
	normals.push_back(normal.y);
	normals.push_back(normal.z);
}

void Mesh::AddUv(Vector3 c)
{
	uv.push_back(c.x);
	uv.push_back(c.y);
	uv.push_back(c.z);
}

void Mesh::AddIndice(uint16_t a, uint16_t b, uint16_t c)
{
	indicies.push_back(a);
	indicies.push_back(b);
	indicies.push_back(c);
}

void Mesh::Update()
{
	glBindBuffer(GL_ARRAY_BUFFER, meshVBO);
	glBufferData(GL_ARRAY_BUFFER, GetFullBufferSize(), NULL, GL_DYNAMIC_DRAW); 

	GLintptr p = 0;

	glBufferSubData(GL_ARRAY_BUFFER, p,  GetVerticiesBufferSize(), vertices.data());
	p += GetVerticiesBufferSize();

	glBufferSubData(GL_ARRAY_BUFFER, p, GetColorsBufferSize(), colors.data());
	p += GetColorsBufferSize();

	glBufferSubData(GL_ARRAY_BUFFER, p, GetNormalsBufferSize(), normals.data());
	p += GetNormalsBufferSize();

	glBufferSubData(GL_ARRAY_BUFFER, p, GetUvBufferSize(), uv.data());

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * indicies.size(), indicies.data(), GL_DYNAMIC_DRAW);
}

int Mesh::GetVerticiesBufferSize()
{
	return sizeof(float) * vertices.size();
}

int Mesh::GetColorsBufferSize()
{
	return sizeof(float) * colors.size();
}

int Mesh::GetNormalsBufferSize()
{
	return sizeof(float) * normals.size();
}

int Mesh::GetUvBufferSize()
{
	return sizeof(float) * uv.size();
}

int Mesh::GetFullBufferSize()
{
	return GetVerticiesBufferSize() + GetColorsBufferSize() + GetNormalsBufferSize() + GetUvBufferSize();
}
