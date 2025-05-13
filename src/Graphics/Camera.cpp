// ==== Camera.cpp ====
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : position(position), worldUp(up), yaw(yaw), pitch(pitch)
{
    updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() const
{
    return glm::lookAt(position, position + front, up);
}

void Camera::MoveForward(float deltaTime)
{
    float speed = 2.5f * deltaTime;
    position += front * speed;
}

void Camera::MoveBackward(float deltaTime)
{
    float speed = 2.5f * deltaTime;
    position -= front * speed;
}

void Camera::MoveLeft(float deltaTime)
{
    float speed = 2.5f * deltaTime;
    position -= glm::normalize(glm::cross(front, up)) * speed;
}

void Camera::MoveRight(float deltaTime)
{
    float speed = 2.5f * deltaTime;
    position += glm::normalize(glm::cross(front, up)) * speed;
}

void Camera::Rotate(float xoffset, float yoffset)
{
    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    pitch = std::clamp(pitch, -89.0f, 89.0f);

    updateCameraVectors();
}

void Camera::updateCameraVectors()
{
    glm::vec3 f;
    f.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    f.y = sin(glm::radians(pitch));
    f.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(f);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}
