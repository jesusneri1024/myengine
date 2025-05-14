// ==== InputManager.cpp ====
#include "InputManager.h"

void InputManager::ProcessInput(GLFWwindow *window, Camera &camera, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.MoveForward(deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.MoveBackward(deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.MoveLeft(deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.MoveRight(deltaTime);

    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // ESC activa el cursor
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        if (!s_CursorEnabled)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            s_CursorEnabled = true;
        }
    }

    // ENTER lo vuelve a ocultar (modo cámara)
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        if (s_CursorEnabled)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            s_CursorEnabled = false;
            ResetMouse(); // Evita saltos bruscos en la cámara
        }
    }
}

void InputManager::MouseCallback(GLFWwindow *window, double xpos, double ypos)
{
    if (!s_Camera || s_CursorEnabled)
        return;

    if (s_FirstMouse)
    {
        s_LastX = xpos;
        s_LastY = ypos;
        s_FirstMouse = false;
    }

    float xoffset = xpos - s_LastX;
    float yoffset = s_LastY - ypos; // Invert Y

    s_LastX = xpos;
    s_LastY = ypos;

    s_Camera->Rotate(xoffset, yoffset);
}

void InputManager::SetCamera(Camera *cam)
{
    s_Camera = cam;
}

void InputManager::ResetMouse()
{
    s_FirstMouse = true;
}

bool InputManager::IsCursorEnabled()
{
    return s_CursorEnabled;
}
