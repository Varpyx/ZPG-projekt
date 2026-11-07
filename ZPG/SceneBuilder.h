#pragma once

#include <memory>
#include <vector>

#include "Scene.h"
#include "Material.h"

class SceneBuilder
{
public:
	std::vector<std::unique_ptr<Scene>> buildScenes(float aspect);

private:
	Material createMaterial(ShaderProgram* shaderProgram, const char* path, int textureUnit, glm::vec3 color = glm::vec3(1.0f));
};
