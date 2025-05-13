#include "Core/Application.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Core/InputManager.h"

static Camera *s_Camera = nullptr;

Application::Application()
    : window(nullptr), camera(glm::vec3(0.0f, 0.0f, 3.0f),
                              glm::vec3(0.0f, 1.0f, 0.0f),
                              -90.0f, 0.0f),
      deltaTime(0.0f), lastFrame(0.0f)
{
    s_Camera = &camera;
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
    glfwSetCursorPosCallback(window, MouseCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        return false;

    glEnable(GL_DEPTH_TEST);

    shader = std::make_unique<Shader>("src/shader_colored.vert", "src/shader_colored.frag");
    model = std::make_unique<Model>("assets/WusonOBJ.obj");

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

        glm::mat4 modelMatrix = glm::mat4(1.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                                (float)windowWidth / windowHeight,
                                                0.1f, 100.0f);

        shader->SetMat4("transform", modelMatrix);
        shader->SetMat4("view", view);
        shader->SetMat4("projection", projection);

        model->Draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Application::ProcessInput()
{
    InputManager::ProcessInput(window, camera, deltaTime);
}

void Application::MouseCallback(GLFWwindow *window, double xpos, double ypos)
{
    s_Camera->ProcessMouseMovement(static_cast<float>(xpos), static_cast<float>(ypos));
}
