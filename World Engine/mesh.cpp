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

void Mesh::RecalculateNormals()
{
	normals.clear();
	normals.resize(0);
	normals.resize(vertices.size(), 0);

	for (int i = 0; i < indicies.size(); i += 3) {
		int vertexIndexA = indicies[i] * 3;
		int vertexIndexB = indicies[i + 1] * 3;
		int vertexIndexC = indicies[i + 2] * 3;

		Vector3 triNormal = SurfaceNormalFromIndices(vertexIndexA, vertexIndexB, vertexIndexC);

		normals[vertexIndexA] += triNormal.x;
		normals[vertexIndexA + 1] += triNormal.y;
		normals[vertexIndexA + 2] += triNormal.z;

		normals[vertexIndexB] += triNormal.x;
		normals[vertexIndexB + 1] += triNormal.y;
		normals[vertexIndexB + 2] += triNormal.z;

		normals[vertexIndexC] += triNormal.x;
		normals[vertexIndexC + 1] += triNormal.y;
		normals[vertexIndexC + 2] += triNormal.z;
	}

	for (int i = 0; i < normals.size(); i += 3) {
		Vector3 r = Vector3(normals[i], normals[i + 1], normals[i + 2]);
		r.Normalize();
		normals[i] = r.x;
		normals[i + 1] = r.y;
		normals[i + 2] = r.z;
	}
}

Vector3 Mesh::SurfaceNormalFromIndices(int a, int b, int c) {
	Vector3 pointA = Vector3(vertices[a], vertices[a + 1], vertices[a + 2]);
	Vector3 pointB = Vector3(vertices[b], vertices[b + 1], vertices[b + 2]);
	Vector3 pointC = Vector3(vertices[c], vertices[c + 1], vertices[c + 2]);

	Vector3 sideAB = pointB - pointA;
	Vector3 sideAC = pointC - pointA;

	Vector3 r = Vector3::Cross(sideAB, sideAC);
	r.Normalize();

	return r;
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
