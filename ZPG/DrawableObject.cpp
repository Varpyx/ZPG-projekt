#include "DrawableObject.h"

DrawableObject::DrawableObject(Model model, const Shader& shader)
	: model_(model), shader_(&shader)
{
}

void DrawableObject::draw() const
{
	shader_->use();
	model_.draw();
}
