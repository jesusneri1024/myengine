#include "Scene/SceneNivel2.h"
#include <glm/glm.hpp>

SceneNivel2::SceneNivel2()
{
    model = std::make_shared<Model>("assets/WusonOBJ.obj");
}

void SceneNivel2::Load()
{
    auto go1 = std::make_shared<GameObject>(model);
    go1->SetPosition(glm::vec3(-1.0f, 0.0f, 0.0f));
    scene.AddObject(go1);
}

void SceneNivel2::Update(float deltaTime)
{
    // Lógica específica de esta escena (si hay)
}

void SceneNivel2::Draw(Shader &shader)
{
    // Lógica de luz diferente a SceneNivel1
    shader.SetVec3("lightDir", glm::normalize(glm::vec3(1.0f, -0.5f, 0.0f))); // luz desde otro ángulo
    shader.SetVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));                // luz azul
    shader.SetVec3("objectColor", glm::vec3(1.0f, 1.0f, 1.0f));               // color de objeto diferente

    scene.Draw(shader);
}
