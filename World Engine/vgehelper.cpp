#include "pch.h"
#include "vgehelper.h"

char* VgeHelper::ReadFile(const char* path) {
	std::ifstream file(path, std::ios::binary);
	char* r;
	size_t size;

	if (!file.is_open())
		throw std::runtime_error("Can't open file on ReadFileToString function.");

	file.seekg(0, std::ios::end);
	size = file.tellg();
	file.seekg(0);

	r = (char*)malloc((size + 1) * sizeof(char));

	file.read(r, size);

	memcpy(&r[size], "\0", 1);

	return r;
}