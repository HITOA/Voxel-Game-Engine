#pragma once
#include <vector>
#include <stdexcept>
#include <filesystem>
#include <map>

#include "vgehelper.h"
//OpenGL related include
#include <GL/glew.h>

#define VGE_VERTICES_POSITION 0
#define VGE_COLORS_POSITION 1
#define VGE_NORMALS_POSITION 2
#define VGE_UV_POSITION 3

#define VGE_UNIFORM_MVP_POSITION 0

#define VGE_VERTEX_SHADER GL_VERTEX_SHADER
#define VGE_FRAGMENT_SHADER GL_FRAGMENT_SHADER
#define VGE_GEOMETRY_SHADER GL_GEOMETRY_SHADER

class Shader
{
public:
	Shader() {};
	Shader(std::filesystem::path dir);
	void AddPass(const char* path, int type);
	bool IsValid();
	GLuint Compile();
	GLuint GetProgramId();
private:
	GLuint programId = NULL;
	std::vector<std::pair<const char*, int>> passes;
	const std::vector<std::pair<std::string, int>> extensions{std::pair("vs", VGE_VERTEX_SHADER), 
		std::pair("fs", VGE_FRAGMENT_SHADER), 
		std::pair("gs", VGE_GEOMETRY_SHADER) };
};

