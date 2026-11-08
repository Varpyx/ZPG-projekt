#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>   
#include <cmath>

Camera::Camera(glm::vec3 eye, glm::vec3 target, float aspect, float fovRadians, float nearPlane, float farPlane)
    : eye_(eye), target_(glm::normalize(target)), fov_(fovRadians), aspect_(aspect), near_(nearPlane), far_(farPlane)
{
    alpha_ = glm::degrees(std::acos(target_.y));
    fi_ = glm::degrees(std::atan2(target_.z, target_.x));
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(eye_, eye_ + target_, up_);
}

glm::mat4 Camera::getProjectionMatrix()
{
    return glm::perspective(fov_, aspect_, near_, far_);
}

void Camera::setAspect(float aspect)
{
    aspect_ = aspect;
    notifyObservers();
}

void Camera::toFront(float d) 
{ 
    eye_ += target_ * d;              
    notifyObservers(); 
}

void Camera::toBack(float d) 
{
    eye_ -= target_ * d;
    notifyObservers();
}

void Camera::toRight(float d) 
{ 
    eye_ += glm::normalize(glm::cross(target_, up_)) * d;
    notifyObservers();
}

void Camera::toLeft(float d) 
{ 
    eye_ -= glm::normalize(glm::cross(target_, up_)) * d;
    notifyObservers();
}

void Camera::toUp(float d) 
{ 
    eye_ += up_ * d;
    notifyObservers();
}

void Camera::toDown(float d) {
    eye_ -= up_ * d;
    notifyObservers();
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
	observer->onCameraChanged(*this);
}

void Camera::notifyObservers()
{
    for(ICameraObserver* observer : observers_)
    {
        observer->onCameraChanged(*this);
	}
}
