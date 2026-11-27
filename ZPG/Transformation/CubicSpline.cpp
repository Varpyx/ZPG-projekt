#include <glm/gtc/matrix_transform.hpp>
#include "CubicSpline.h"
#include <cmath>


CubicSpline::CubicSpline(std::vector<glm::vec3> points, float speed) : points_(std::move(points)), speed_(speed)
{
}

glm::vec3 CubicSpline::bezier(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, float u) {
	float mu = 1.0f - u;
	return mu * mu * mu * p0
		+ 3.0f * mu * mu * u * p1
		+ 3.0f * mu * u * u * p2
		+ u * u * u * p3;
}

glm::mat4 CubicSpline::getModelMatrix()
{
	int segments = (static_cast<int>(points_.size()) - 1) / 3;
	if (segments < 1) return glm::mat4(1.0f);

	float scaled = t_ * segments;
	int seg = std::min(static_cast<int>(scaled), segments - 1);
	float u = scaled - seg;

	int i = 3 * seg;
	glm::vec3 p0 = points_[i], p1 = points_[i + 1], p2 = points_[i + 2], p3 = points_[i + 3];

	// position P(t)
	glm::vec3 position = bezier(p0, p1, p2, p3, u);

	// direction P'(t), multiplied out
	float mu = 1.0f - u;
	glm::vec3 tangent = -3.0f * mu * mu * p0
		+ (3.0f * mu * mu - 6.0f * mu * u) * p1
		+ (6.0f * mu * u - 3.0f * u * u) * p2
		+ 3.0f * u * u * p3;

	// rotation angle phi = atan2(P'y, P'x)
	// continuity at joint P3: C0 = shared point only (corner, rotation jumps),
	// G1 = P2,P3,P4 on one line (smooth rotation, speed jumps),
	// C1 = P3-P2 == P4-P3 (smooth rotation and speed). Here it is given by the points.
	float angle = std::atan2(tangent.y, tangent.x);

	glm::mat4 m = glm::translate(glm::mat4(1.0f), position);
	return glm::rotate(m, angle, glm::vec3(0.0f, 0.0f, 1.0f));
}

void CubicSpline::update(float deltaTime)
{
	t_ += direction_ * speed_ * deltaTime;
	if (t_ >= 1.0f) { t_ = 1.0f; direction_ = -1; }
	else if (t_ <= 0.0f) { t_ = 0.0f; direction_ = 1; }
}

void CubicSpline::setPoint(int index, glm::vec3 pos)
{
	if (index < 0 || index >= static_cast<int>(points_.size())) return;
	points_[index] = pos;
}