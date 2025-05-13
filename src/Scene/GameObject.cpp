#include "Scene/GameObject.h"
#include <glm/gtc/matrix_transform.hpp>

GameObject::GameObject(std::shared_ptr<Model> model)
    : model(model), position(0.0f), rotation(0.0f), scale(1.0f) {}

void GameObject::Draw(Shader &shader)
{
    glm::mat4 modelMatrix = GetModelMatrix();
    shader.SetMat4("transform", modelMatrix);
    model->Draw();
}

void GameObject::SetPosition(const glm::vec3 &pos)
{
    position = pos;
}

void GameObject::SetRotation(const glm::vec3 &rot)
{
    rotation = rot;
}

void GameObject::SetScale(const glm::vec3 &scl)
{
    scale = scl;
}

glm::vec3 GameObject::GetPosition() const
{
    return position;
}

glm::vec3 GameObject::GetRotation() const
{
    return rotation;
}

glm::vec3 GameObject::GetScale() const
{
    return scale;
}

glm::mat4 GameObject::GetModelMatrix() const
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));
    model = glm::scale(model, scale);
    return model;
}
