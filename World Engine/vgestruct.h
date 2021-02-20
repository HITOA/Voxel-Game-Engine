#pragma once
#include <vector>

#include "shader.h"
#include "scene.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct VgeAppData {
	const char* wName;
	int wWidth;
	int wHeight;
	int wAttrib;
};

struct VgeGlfwData {
	GLFWwindow* window;
	GLFWmonitor* monitor;
};

struct VgeEngineData {
	std::vector<Shader> shaders;
};
