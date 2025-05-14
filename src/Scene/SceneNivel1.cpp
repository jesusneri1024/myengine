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
    // Parámetros de luz (aquí está ahora la lógica de luz)
    shader.SetVec3("lightDir", glm::normalize(glm::vec3(-0.2f, -1.0f, -0.3f)));
    shader.SetVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    shader.SetVec3("objectColor", glm::vec3(1.0f, 0.7f, 0.3f)); // Cambia el color del objeto si quieres

    scene.Draw(shader);
}
