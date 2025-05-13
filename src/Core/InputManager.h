#pragma once
#include <GLFW/glfw3.h>
#include "Graphics/Camera.h"

class InputManager
{
public:
    static void ProcessInput(GLFWwindow *window, Camera &camera, float deltaTime);
};
