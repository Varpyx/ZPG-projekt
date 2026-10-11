#pragma once

// Include GLM
#include <glm/glm.hpp>
#include <vector>
#include <memory>

//Michal Poncza
class Transformation
{
public:
	virtual	~Transformation() = default;
	virtual glm::mat4 getModelMatrix() = 0;
	virtual void update(float deltaTime) {};
};


class Translation : public Transformation
{
public:
	Translation(const glm::vec3& offset = glm::vec3(0.0f), const glm::vec3& velocity = glm::vec3(0.0f)) : offset_(offset), velocity_(velocity){};
	glm::mat4 getModelMatrix() override;
	void update(float deltaTime) override { offset_ += velocity_ * deltaTime; }

	void setOffset(const glm::vec3& offset) { offset_ = offset; }
	void setVelocity(const glm::vec3& velocity) { velocity_ = velocity; }
	glm::vec3 getOffset() const { return offset_; }
	glm::vec3 getVelocity() const { return velocity_; }
private:
	glm::vec3 offset_ = glm::vec3(0.0f);
	glm::vec3 velocity_ = glm::vec3(0.0f);

};

class Rotation : public Transformation
{
public:
	Rotation(const glm::vec3& axis, float angle = 0.0f, float speed = 0.0f)
		: axis_(axis), angle_(angle), speed_(speed) {};
	glm::mat4 getModelMatrix() override;
	void update(float deltaTime) override { angle_ += speed_ * deltaTime; }

	void setAngle(float angle) { angle_ = angle; }
	void setSpeed(float speed) { speed_ = speed; }
	float getAngle() const { return angle_; }
	float getSpeed() const { return speed_; }
private:
	glm::vec3 axis_ = glm::vec3(0.0f, 1.0f, 0.0f);
	float angle_ = 0.0f;
	float speed_ = 0.0f;
};

class Scale : public Transformation
{
public:
	Scale(float scale = 1.0f)
		: scale_(scale) {
	};
	glm::mat4 getModelMatrix() override;

	void setScale(float scale) { scale_ = scale; }
	float getScale() { return scale_; }
private:
	float scale_ = 1.0f;
};

class CompositeTransformation : public Transformation
{
public:
	void addTransformation(std::unique_ptr<Transformation> transformation);
	glm::mat4 getModelMatrix() override;
	void update(float deltaTime) override;
private:
	std::vector<std::unique_ptr<Transformation>> transformations_;
};