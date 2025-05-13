#include "Scene/Scene.h"

void Scene::AddObject(std::shared_ptr<GameObject> object)
{
    objects.push_back(object);
}

void Scene::Draw(Shader &shader)
{
    for (const auto &obj : objects)
    {
        obj->Draw(shader);
    }
}
