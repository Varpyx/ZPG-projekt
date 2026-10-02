#include "DrawableObject.h"

DrawableObject::DrawableObject(Model model, ShaderProgram* shaderProgram)
	: model_(model), shaderProgram_(shaderProgram)
{
}

void DrawableObject::draw() const
{
	if (shaderProgram_ && shaderProgram_->use())
	{
		model_.draw();
	}
}