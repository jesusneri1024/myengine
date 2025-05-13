// src/Scene/SceneNivel1.cpp
#include "Scene/SceneNivel1.h"
#include <glm/glm.hpp>

SceneNivel1::SceneNivel1()
{
    model = std::make_shared<Model>("assets/WusonOBJ.obj");
}

void SceneNivel1::Load()
{
    auto go1 = std::make_shared<GameObject>(model);
    go1->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    scene.AddObject(go1);

    auto go2 = std::make_shared<GameObject>(model);
    go2->SetPosition(glm::vec3(2.0f, 0.0f, 0.0f));
    scene.AddObject(go2);
}

void SceneNivel1::Update(float deltaTime)
{
    // Aquí podrías mover objetos, detectar colisiones, etc.
}

void SceneNivel1::Draw(Shader &shader)
{
    scene.Draw(shader);
}
