#pragma once
#include <vector>
#include <string>
#include "vector3.h"
#include "vector2.h"
#include "shader.h"

//OpenGL related include
#include <GL/glew.h>

enum class FaceCullingMode {
	FRONT = GL_FRONT,
	BACK = GL_BACK,
	FRONT_AND_BACK = GL_FRONT_AND_BACK
};

class Material
{
public:
	FaceCullingMode Culling;
	Material(unsigned int programId);
	void SetActive();
	void SetFloat(const std::string& name, float value);
	void SetVec2(const std::string& name, Vector2 value);
	void SetVec3(const std::string& name, Vector3 value);
private:
	unsigned int programId;
	GLuint vao;
	std::vector<std::pair<int, std::pair<float*, int>>> materialData;
	void Init();
	float* AllocData(int size, float* data);
};

