#pragma once

#include <memory>
#include <GLFW/glfw3.h>

#include "Graphics/Shader.h"
#include "Graphics/Camera.h"
#include "Scene/IScene.h"

class Application
{
public:
    Application();
    ~Application();

    bool Init(int width, int height, const char *title);
    void Run();

private:
    void ProcessInput();

    GLFWwindow *window;
    int windowWidth;
    int windowHeight;

    std::unique_ptr<Shader> shader;
    Camera camera;
    std::unique_ptr<IScene> activeScene;

    float deltaTime;
    float lastFrame;
};
