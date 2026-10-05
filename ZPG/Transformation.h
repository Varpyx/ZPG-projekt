#pragma once

// Include GLM
#include <glm/glm.hpp>

// Transformation without using matirx for now
class Transformation
{
public:
	Transformation() = default;

	void translate(const glm::vec3& delta);
	void rotateY(float alpha);
	void rotatePlaneXY(float alpha);

	void setScale(float scale);
	void setOffset(const glm::vec3& offset) { offset_ = offset; }
	void addScale(float deltaScale) { scale_ += deltaScale; if (scale_ < 0.01f) scale_ = 0.01f; }

	void reset();

	const glm::vec3& getOffset() const { return offset_; }
	float getAngleY() const { return angleY_; }
	float getAnglePlaneXY() const { return anglePlaneXY_; }
	float getScale() const { return scale_; }
	glm::mat4 getModelMatrix();

private:
	glm::vec3 offset_ = glm::vec3(0.0f);
	float angleY_ = 180.0f;
	float anglePlaneXY_ = 30.0f;
	float scale_ = 1.0f;
	glm::mat4 M = glm::mat4(1.0f);
};