#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

#include "Graphics/Shader.h"
#include "Graphics/Camera.h"
#include "Model/Model.h"

class Application
{
public:
    Application();
    ~Application();

    bool Init(int width, int height, const char *title);
    void Run();

private:
    GLFWwindow *window;
    int windowWidth, windowHeight;

    std::unique_ptr<Shader> shader;
    std::unique_ptr<Model> model;
    Camera camera;

    float deltaTime;
    float lastFrame;

    void ProcessInput();
};
