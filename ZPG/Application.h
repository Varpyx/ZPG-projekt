#pragma once

#include "Scene.h"

#include <cstddef>
#include <vector>
#include <memory>
#include "SceneBuilder.h"

struct GLFWwindow;

class Application  
{  
public:  
    Application() = default;  
    void initialization();  
    void createScenes();  
    void run();  

    void onWindowResize(int width, int height);  
    void onCursorPos(double x, double y);  
    void switchScene(size_t index); 
    void processCameraInput(float deltaTime);
private:  
    GLFWwindow* window_ = nullptr;  
    std::vector<std::unique_ptr<Scene>> scenes_;  
    size_t activeScene_ = 0;  
	SceneBuilder sceneBuilder_;

	float moveSpeed_ = 1.5f;
    double lastX_ = 400.0;  
    double lastY_ = 300.0;  
    float aspect_ = 4.0f / 3.0f;  
};
