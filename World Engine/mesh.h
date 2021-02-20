#pragma once
#include <vector>

#include <GL/glew.h>

class Mesh
{
public:
	 std::vector<float> verticies;
	 GLuint vbo;
	 Mesh();
	 void Update();
};

