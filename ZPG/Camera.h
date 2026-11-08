#pragma once
#include <glm/glm.hpp>
#include "ICameraObserver.h"
#include <vector>

//Michal Poncza
class Camera
{
public:
    Camera(glm::vec3 eye = glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3 target = glm::vec3(0.0f, 0.0f, -1.0f),float aspect = 4.0f / 3.0f,
        float fovRadians = glm::radians(60.0f), float nearPlane = 0.1f, float farPlane = 100.0f);

    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();

    void setAspect(float aspect);

    void toFront(float d);
    void toBack(float d);
    void toRight(float d);
    void toLeft(float d);
    void toUp(float d);
    void toDown(float d);

    void processMouse(float x, float y);
    void addObserver(ICameraObserver* observer);
	void notifyObservers();
    glm::vec3 getCameraPosition() { return eye_; }
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
	float sens_ = 0.2f;

	std::vector<ICameraObserver*> observers_;
};