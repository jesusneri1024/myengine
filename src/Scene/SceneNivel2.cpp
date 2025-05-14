#include "Scene/SceneNivel2.h"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

// En SceneNivel2.h
float lightAngle = 0.0f;

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
    // Aumentamos el ángulo en radianes con el tiempo
    lightAngle += glm::radians(45.0f) * deltaTime; // 45 grados por segundo

    // Puedes envolver el ángulo si quieres que no crezca infinitamente
    if (lightAngle > 2.0f * glm::pi<float>())
        lightAngle -= 2.0f * glm::pi<float>();
}

void SceneNivel2::Draw(Shader &shader)
{

    // Dirección giratoria de la luz
    glm::vec3 lightDir = glm::vec3(cos(lightAngle), -0.5f, sin(lightAngle));
    shader.SetVec3("lightDir", glm::normalize(lightDir));

    shader.SetVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));  // luz azul
    shader.SetVec3("objectColor", glm::vec3(1.0f, 1.0f, 1.0f)); // color de objeto diferente

    scene.Draw(shader);
}
