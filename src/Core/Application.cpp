// src/Core/Application.cpp

#include <glad/glad.h>
#include "Core/Application.h"
#include "Core/InputManager.h"
#include "Scene/SceneNivel1.h"
#include "Scene/SceneNivel2.h"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Application::Application()
    : window(nullptr),
      camera(glm::vec3(0.0f, 0.0f, 3.0f),
             glm::vec3(0.0f, 1.0f, 0.0f),
             -90.0f, 0.0f),
      deltaTime(0.0f),
      lastFrame(0.0f),
      tabPressed(false),
      currentSceneIndex(0)
{
}

Application::~Application()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool Application::Init(int width, int height, const char *title)
{
    windowWidth = width;
    windowHeight = height;

    if (!glfwInit())
        return false;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window)
        return false;

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetCursorPosCallback(window, InputManager::MouseCallback);
    InputManager::SetCamera(&camera);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        return false;

    glEnable(GL_DEPTH_TEST);

    shader = std::make_unique<Shader>("src/shader_colored.vert", "src/shader_colored.frag");

    // Registrar escenas
    auto nivel1 = std::make_shared<SceneNivel1>();
    auto nivel2 = std::make_shared<SceneNivel2>();
    nivel1->Load();
    nivel2->Load();

    scenes.push_back(nivel1);
    scenes.push_back(nivel2);

    return true;
}

void Application::Run()
{
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        ProcessInput();

        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->Use();

        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                                (float)windowWidth / windowHeight,
                                                0.1f, 100.0f);

        shader->SetMat4("view", view);
        shader->SetMat4("projection", projection);

        scenes[currentSceneIndex]->Update(deltaTime);
        scenes[currentSceneIndex]->Draw(*shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Application::ProcessInput()
{
    InputManager::ProcessInput(window, camera, deltaTime);

    // Detectar Tab para cambiar de escena
    if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS && !tabPressed)
    {
        tabPressed = true;
        SwitchScene();
    }
    else if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE)
    {
        tabPressed = false;
    }
}

void Application::SwitchScene()
{
    currentSceneIndex = (currentSceneIndex + 1) % scenes.size();
    std::cout << "Changing Scene #" << currentSceneIndex << std::endl;
}
