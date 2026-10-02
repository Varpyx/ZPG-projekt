#pragma once

// Include GLM
#include <glm/glm.hpp>

// Transformace pocitane pomoci rovnic (bez matic).
// Samotny vypocet dela vertex shader, tato trida drzi jen parametry,
// ktere se posilaji jako uniformni promenne.
class Transformation
{
public:
	Transformation() = default;

	// posun (translace)
	void translate(const glm::vec3& delta);
	// rotace v prostoru kolem osy y
	void rotateY(float alpha);
	// rotace v rovine xy kolem pocatku, proti smeru hodinovych rucicek
	void rotatePlaneXY(float alpha);
	// zmena meritka
	void setScale(float scale);

	void reset();

	const glm::vec3& getOffset() const { return offset_; }
	float getAngleY() const { return angleY_; }
	float getAnglePlaneXY() const { return anglePlaneXY_; }
	float getScale() const { return scale_; }

private:
	glm::vec3 offset_ = glm::vec3(0.0f);
	float angleY_ = 0.0f;
	float anglePlaneXY_ = 0.0f;
	float scale_ = 1.0f;
};