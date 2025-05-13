// src/Scene/SceneNivel2.cpp
#include "Scene/SceneNivel2.h"
#include <glm/glm.hpp>

SceneNivel2::SceneNivel2()
{
    model = std::make_shared<Model>("assets/WusonOBJ.obj");
}

void SceneNivel2::Load()
{
    auto go = std::make_shared<GameObject>(model);
    go->SetPosition(glm::vec3(-2.0f, 1.0f, 0.0f));
    scene.AddObject(go);
}

void SceneNivel2::Update(float deltaTime)
{
    // Ejemplo de animación si deseas
}

void SceneNivel2::Draw(Shader &shader)
{
    scene.Draw(shader);
}
