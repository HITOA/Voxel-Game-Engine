#include "pch.h"
#include "shader.h"

void Shader::AddPass(const char* path, int type) {
	passes.push_back(std::make_pair(path, type));
}

void Shader::Init() {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
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

	mvp = glGetUniformLocation(programId, "MVP");

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

GLuint Shader::GetMVP()
{
	return mvp;
}
