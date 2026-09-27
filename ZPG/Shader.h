#pragma once

class Shader
{
public:
	// Empty on purpose, the program is linked later in Application::createScene.
	Shader() = default;

	// Compiles both shaders and links them into one program.
	Shader(const char* vertexFile, const char* fragmentFile);

	// Makes this program the active one for drawing.
	void use() const;

private:
	unsigned int id_ = 0;
};
