#pragma once

#include "vector3.h"
#include <vector>
#include <GL/glew.h>

class Mesh
{
public:
	 std::vector<float> vertices;
	 std::vector<float> colors;
	 std::vector<float> normals;
	 std::vector<float> uv;
	 std::vector<uint16_t> indicies;
	 GLuint meshVBO;
	 GLuint indicesVBO;
	 Mesh();
	 void Bind();
	 void AddVertex(Vector3 vertex);
	 void AddColor(Vector3 color);
	 void AddNormals(Vector3 normal);
	 void AddUv(Vector3 c);
	 void AddIndice(uint16_t a, uint16_t b, uint16_t c);
	 void RecalculateNormals();
	 Vector3 SurfaceNormalFromIndices(int a, int b, int c);
	 void Update();
	 int GetVerticiesBufferSize();
	 int GetColorsBufferSize();
	 int GetNormalsBufferSize();
	 int GetUvBufferSize();
	 int GetFullBufferSize();
};

