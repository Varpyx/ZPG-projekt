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

private:
    glm::vec3 eye_;
    glm::vec3 target_;
    glm::vec3 up_ = glm::vec3(0.0f, 1.0f, 0.0f);

    float fov_;
    float aspect_;
    float near_;
    float far_;
};