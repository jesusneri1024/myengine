// src/Core/Application.h
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
    void SwitchScene();

    GLFWwindow *window;
    int windowWidth;
    int windowHeight;

    std::unique_ptr<Shader> shader;
    Camera camera;

    float deltaTime;
    float lastFrame;

    bool tabPressed;

    std::vector<std::shared_ptr<IScene>> scenes;
    int currentSceneIndex;
};
