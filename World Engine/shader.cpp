#include "pch.h"
#include "shader.h"

Shader::Shader(std::filesystem::path dir)
{
	std::filesystem::directory_iterator begin(dir);

	for (auto& file : begin) {
		std::filesystem::path fileExt = file.path().extension();

		for (int i = 0; i < extensions.size(); i++) {
			if (fileExt.string().find(extensions[i].first) != std::string::npos) {

				char* path = (char*)malloc(sizeof(char) * file.path().string().size() + 1);
				memcpy(path, file.path().string().c_str(), sizeof(char) * file.path().string().size() + 1);

				this->passes.push_back(std::make_pair(path, extensions[i].second));
				break;
			}
		}
	}
}

void Shader::AddPass(const char* path, int type) {
	passes.push_back(std::make_pair(path, type));
}

bool Shader::IsValid()
{
	return passes.size() > 1;
}

void Shader::Init() {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnableVertexAttribArray(VGE_VERTICES_POSITION);
	glEnableVertexAttribArray(VGE_COLORS_POSITION);
	glEnableVertexAttribArray(VGE_NORMALS_POSITION);
	glEnableVertexAttribArray(VGE_UV_POSITION);
}

GLuint Shader::Compile() {
	if (programId != NULL)
		return programId;
	programId = glCreateProgram();

	GLint Result = GL_FALSE;
	int InfoLogLength;

	std::vector<unsigned int> sIDs;

	for (std::pair<const char*, int>& pass : passes) {
		unsigned int sID = glCreateShader(pass.second);

		char* source = VgeHelper::ReadFile(pass.first);

		glShaderSource(sID, 1, &source, NULL);
		glCompileShader(sID);

		free(source);

		glGetShaderiv(sID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(sID, GL_INFO_LOG_LENGTH, &InfoLogLength);

		if (InfoLogLength > 0) {
			char* errMsg = (char*)malloc(InfoLogLength + 1);
			glGetShaderInfoLog(sID, InfoLogLength, NULL, errMsg);
			throw std::runtime_error(errMsg);
		}

		glAttachShader(programId, sID);

		sIDs.push_back(sID);
	}

	glLinkProgram(programId);

	glGetProgramiv(programId, GL_LINK_STATUS, &Result);
	glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &InfoLogLength);

	if (InfoLogLength > 0) {
		char* errMsg = (char*)malloc(InfoLogLength + 1);
		glGetProgramInfoLog(programId, InfoLogLength, NULL, errMsg);
		throw std::runtime_error(errMsg);
	}

	for (unsigned int& sID : sIDs) {
		glDetachShader(programId, sID);
		glDeleteShader(sID);
	}

	sIDs.clear();

	return programId;
}

void Shader::SetActive() {
	glBindVertexArray(vao);
	glUseProgram(programId);
}

GLuint Shader::GetProgramId() {
	return programId;
}

GLuint Shader::GetVAO() {
	return vao;
}