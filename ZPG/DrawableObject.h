#pragma once

#include "Model.h"
#include "Shader.h"

class DrawableObject
{
public:
	DrawableObject(Model model, const Shader& shader);

	void draw() const;

private:
	Model model_;
	const Shader* shader_ = nullptr;
};
