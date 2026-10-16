#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>   

Camera::Camera(const glm::vec3& eye, const glm::vec3& target, float aspect, float fovRadians, float nearPlane, float farPlane)
    : eye_(eye), target_(glm::normalize(target)), fov_(fovRadians), aspect_(aspect), near_(nearPlane), far_(farPlane)
{
    alpha_ = 90.0f;
	fi_ = 270.0f;

}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(eye_, eye_ + target_, up_);
}

glm::mat4 Camera::getProjectionMatrix()
{
    return glm::perspective(fov_, aspect_, near_, far_);
}

void Camera::processMouse(float x, float y)
{
	fi_ += x * sens_;
	alpha_ += y * sens_;

    if (alpha_ <= 1.0f) alpha_ = 1.0f;
    if (alpha_ >= 179.0f) alpha_ = 179.0f;

    float radAlpha = glm::radians(alpha_);
    float radFi = glm::radians(fi_);

    target_.x = std::sin(radAlpha) * std::cos(radFi);
    target_.z = std::sin(radAlpha) * std::sin(radFi);
    target_.y = std::cos(radAlpha);

    target_ = glm::normalize(target_);
    notifyObservers();
}

void Camera::addObserver(ICameraObserver* observer)
{
	observers_.push_back(observer);
	observer->onCameraChanged(getViewMatrix(), getProjectionMatrix());
}

void Camera::notifyObservers()
{
    for(ICameraObserver* observer : observers_)
    {
        observer->onCameraChanged(getViewMatrix(), getProjectionMatrix());
	}
}
