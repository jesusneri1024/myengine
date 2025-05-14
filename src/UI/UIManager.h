#pragma once

#include <GLFW/glfw3.h>

class UIManager
{
public:
    static void Init(GLFWwindow *window);
    static void BeginFrame();
    static void EndFrame();
    static void Shutdown();

    static void RenderMainUI(); // para tu menú, FPS, etc.
};
