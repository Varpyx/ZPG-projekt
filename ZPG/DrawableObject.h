#pragma once

#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"

class DrawableObject
{
public:
	DrawableObject(Model model, ShaderProgram* shaderProgram);
	void draw() const;

private:
	Model model_;
	Transformation transformation_;
	ShaderProgram* shaderProgram_ = nullptr;
};