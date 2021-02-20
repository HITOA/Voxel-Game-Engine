#pragma once
#include <vector>
#include "shader.h"
//OpenGL related include
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Material
{
public:
	Material();
private:
	Shader shader;
};

