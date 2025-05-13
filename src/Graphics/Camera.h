#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class Camera
{
public:
    Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);

    glm::mat4 GetViewMatrix() const;
    void ProcessKeyboard(GLFWwindow *window, float deltaTime);
    void ProcessMouseMovement(float xpos, float ypos);

    glm::vec3 GetPosition() const { return position; }
    glm::vec3 GetFront() const { return front; }

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float yaw;
    float pitch;

    float lastX;
    float lastY;
    bool firstMouse;

    void updateCameraVectors();
};
