#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>   

Camera::Camera(const glm::vec3& eye, const glm::vec3& target, float aspect,
    float fovRadians, float nearPlane, float farPlane)
    : eye_(eye),
    target_(glm::normalize(target)),
    fov_(fovRadians),
    aspect_(aspect),
    near_(nearPlane),
    far_(farPlane)
{
}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(eye_, eye_ + target_, up_);
}

glm::mat4 Camera::getProjectionMatrix() const
{
    return glm::perspective(fov_, aspect_, near_, far_);
}