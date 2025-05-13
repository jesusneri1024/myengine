#pragma once

#include <glm/glm.hpp>
#include <memory>
#include "Model/Model.h"
#include "Graphics/Shader.h"

class GameObject
{
public:
    GameObject(std::shared_ptr<Model> model);

    void Draw(Shader &shader);

    void SetPosition(const glm::vec3 &pos);
    void SetRotation(const glm::vec3 &rot);
    void SetScale(const glm::vec3 &scl);

    glm::vec3 GetPosition() const;
    glm::vec3 GetRotation() const;
    glm::vec3 GetScale() const;

private:
    glm::mat4 GetModelMatrix() const;

    std::shared_ptr<Model> model;
    glm::vec3 position;
    glm::vec3 rotation; // En grados
    glm::vec3 scale;
};
