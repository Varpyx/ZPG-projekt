#pragma once
#include <vector>
#include "glm/glm.hpp"
#include "Transformation.h"

class CubicSpline : public Transformation
{
public:
	CubicSpline(std::vector<glm::vec3> points, float speed = 0.2f);

	glm::mat4 getModelMatrix() override;
	void update(float deltaTime) override;
	void setPoint(int index, glm::vec3 pos);
private:
	static glm::vec3 bezier(const glm::vec3& p0, const glm::vec3& p1,
		const glm::vec3& p2, const glm::vec3& p3, float u);

	std::vector<glm::vec3> points_;
	float speed_;
	float t_ = 0.0f;
	int direction_ = 1;
};