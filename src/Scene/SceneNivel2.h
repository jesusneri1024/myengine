#pragma once

#include "Scene/IScene.h"
#include "Scene/Scene.h"
#include "Scene/GameObject.h"
#include "Model/Model.h"
#include <memory>

class SceneNivel2 : public IScene
{
public:
    SceneNivel2();

    void Load() override;
    void Update(float deltaTime) override;
    void Draw(Shader &shader) override;

private:
    Scene scene;
    std::shared_ptr<Model> model;
};
