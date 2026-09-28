#pragma once

class Shader
{
public:
	Shader() = default;
	Shader(const char* vertexFile, const char* fragmentFile);
	void use() const;

private:
	unsigned int id_ = 0;
};
