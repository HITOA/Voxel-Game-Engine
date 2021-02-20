#pragma once
#include <vector>
#include <stdexcept>

#include "vgehelper.h"
//OpenGL related include
#include <GL/glew.h>

#define VGE_VERTEX_SHADER GL_VERTEX_SHADER
#define VGE_FRAGMENT_SHADER GL_FRAGMENT_SHADER

class Shader
{
public:
	void Init();
	void AddPass(const char* path, int type);
	GLuint Compile();
	void SetActive();
	GLuint GetProgramId();
	GLuint GetVAO();
	GLuint GetMVP();
private:
	GLuint programId = NULL;
	GLuint vao;
	GLuint mvp;
	std::vector<std::pair<const char*, int>> passes;
};

