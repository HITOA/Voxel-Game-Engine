#include "pch.h"
#include "material.h"

Material::Material(unsigned int programId)
{
	Culling = FaceCullingMode::BACK;
	this->programId = programId;
	Init();
}

void Material::SetActive()
{
	glBindVertexArray(vao);
	glUseProgram(programId);

	for (auto& data : materialData) {
		switch (data.second.second) {
			case 1:
				glUniform1fv(data.first, 1, data.second.first);
				break;
			case 2:
				glUniform2fv(data.first, 1, data.second.first);
				break;
			case 3:
				glUniform3fv(data.first, 1, data.second.first);
				break;
			case 4:
				glUniform4fv(data.first, 1, data.second.first);
				break;
		}
	}
}

void Material::SetFloat(const std::string& name, float value)
{
	unsigned int location = glGetUniformLocation(programId, (std::string("material.") + name).c_str());

	float* data = AllocData(1, &value);

	for (auto& d : materialData) {
		if (d.first == location) {
			free(d.second.first);
			d.second.first = data;
			d.second.second = 1;
			return;
		}
	}

	materialData.push_back(std::make_pair(location, std::make_pair(data, 1)));
}

void Material::SetVec2(const std::string& name, Vector2 value)
{
	unsigned int location = glGetUniformLocation(programId, (std::string("material.") + name).c_str());

	float* data = AllocData(2, &value.x);

	for (auto& d : materialData) {
		if (d.first == location) {
			free(d.second.first);
			d.second.first = data;
			d.second.second = 2;
			return;
		}
	}

	materialData.push_back(std::make_pair(location, std::make_pair(data, 2)));
}

void Material::SetVec3(const std::string& name, Vector3 value)
{
	unsigned int location = glGetUniformLocation(programId, (std::string("material.") + name).c_str());

	float* data = AllocData(3, &value.x);

	for (auto& d : materialData) {
		if (d.first == location) {
			free(d.second.first);
			d.second.first = data;
			d.second.second = 3;
			return;
		}
	}

	materialData.push_back(std::make_pair(location, std::make_pair(data, 3)));
}

void Material::Init()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnableVertexAttribArray(VGE_VERTICES_POSITION);
	glEnableVertexAttribArray(VGE_COLORS_POSITION);
	glEnableVertexAttribArray(VGE_NORMALS_POSITION);
	glEnableVertexAttribArray(VGE_UV_POSITION);

	glBindVertexArray(0);
}

float* Material::AllocData(int size, float* data)
{
	float* r = (float*)malloc(sizeof(float) * size);
	memcpy(r, data, sizeof(float) * size);
	return r;
}
