#pragma once

#include <vector>
#include <memory>
#include "Scene/GameObject.h"
#include "Graphics/Shader.h"

class Scene
{
public:
    void AddObject(std::shared_ptr<GameObject> object);
    void Draw(Shader &shader);

private:
    std::vector<std::shared_ptr<GameObject>> objects;
};
