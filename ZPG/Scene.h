#pragma once

#include "DrawableObject.h"
#include "ShaderProgram.h"

#include <deque>
#include <vector>

class Scene
{
public:
	ShaderProgram* addShaderProgram(const char* vertexFile, const char* fragmentFile);
	void addDrawableObject(Model model, ShaderProgram* shaderProgram);
	void draw() const;

private:
	// deque, ne vector: pri push_back neprevede existujici prvky,
	// takze ukazatele v DrawableObject zustavaji platne
	std::deque<ShaderProgram> programs_;
	std::vector<DrawableObject> objects_;
};