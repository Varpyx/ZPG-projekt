#pragma once

// Include GLAD
#include <glad/gl.h>

// Include GLM
#include <glm/glm.hpp>
#include "Shader.h"
#include "ICameraObserver.h"

//Michal Poncza
class ShaderProgram : public ICameraObserver
{
public:
	ShaderProgram(const char* vertexFile, const char* fragmentFile);
	bool use() const;

	void onCameraChanged(glm::mat4 viewMatrix, glm::mat4 projectionMatrix,glm::vec3 cameraPos) override;
	void updateCameraUniforms();

	void setUniform(const char* name, float value);
	void setUniform(const char* name, int value);
	void setUniform(const char* name, const glm::vec3& value);
	void setUniform(const char* name, const glm::mat4& value);
	void setUniform(const char* name, const glm::vec4& value);

private:
	Shader vertexShader_;
	Shader fragmentShader_;
	GLuint id_ = 0;

	glm::mat4 viewMatrix_ = glm::mat4(1.0f);
	glm::mat4 projectionMatrix_ = glm::mat4(1.0f);
	glm::vec3 cameraPos_ = glm::vec3(0.0f, 0.0f, 3.0f);
	bool camChanged_ = true;
};