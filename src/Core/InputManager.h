// ==== InputManager.h ====
#pragma once
#include <GLFW/glfw3.h>
#include "Camera.h"

class InputManager
{
public:
    static void ProcessInput(GLFWwindow *window, Camera &camera, float deltaTime);
    static void MouseCallback(GLFWwindow *window, double xpos, double ypos);
    static void SetCamera(Camera *cam);

private:
    static inline Camera *s_Camera = nullptr;
    static inline bool s_FirstMouse = true;
    static inline float s_LastX = 400.0f;
    static inline float s_LastY = 300.0f;
};