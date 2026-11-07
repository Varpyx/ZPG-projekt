#include "Material.h"
#include <glad/gl.h>

Material::Material(ShaderProgram* shaderProgram, glm::vec3 color) : shaderProgram_(shaderProgram), color_(color)
{
}

void Material::setTexture(Texture* texture, int textureUnit)
{
	if (!texture) return;

	textureID_ = texture->getID();
	textureUnit_ = textureUnit;
}

void Material::bind()
{
	if (!shaderProgram_) return;

	shaderProgram_->use();

	if(textureID_ != 0)
	{
		glActiveTexture(GL_TEXTURE0 + textureUnit_);
		glBindTexture(GL_TEXTURE_2D, textureID_);
		shaderProgram_->setUniform("textureUnitID", textureUnit_);
	}

	shaderProgram_->setUniform("fragmentColor", color_);
}
