#pragma once
#include <glm/glm.hpp>
#include <glm/ext/scalar_constants.hpp>

class Camera
{
public:
    Camera(const glm::vec3& eye = glm::vec3(0.0f, 0.0f, 3.0f),
        const glm::vec3& target = glm::vec3(0.0f, 0.0f, -1.0f),
        float aspect = 4.0f / 3.0f,
        float fovRadians = glm::radians(60.0f),
        float nearPlane = 0.1f,
        float farPlane = 100.0f);

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;

    void setAspect(float aspect) { aspect_ = aspect; }

    void toFront(float d) { eye_ += target_ * d; }
    void toBack(float d) { eye_ -= target_ * d; }
    void toRight(float d) { eye_ += glm::normalize(glm::cross(target_, up_)) * d; }
    void toLeft(float d) { eye_ -= glm::normalize(glm::cross(target_, up_)) * d; }
	void toUp(float d) { eye_ += up_ * d; }
	void toDown(float d) { eye_ -= up_ * d; }

    void processMouse(float x, float y);

private:
    glm::vec3 eye_;
    glm::vec3 target_;
    glm::vec3 up_ = glm::vec3(0.0f, 1.0f, 0.0f);

    float fov_;
    float aspect_;
    float near_;
    float far_;

    float fi_; 
	float alpha_;
	float sens_ = 0.1f;
};