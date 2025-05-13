// src/Scene/IScene.h
#pragma once

#include "Graphics/Shader.h"

class IScene
{
public:
    virtual ~IScene() = default;

    // Se llama una vez al cargar la escena (para crear objetos, etc.)
    virtual void Load() = 0;

    // Se llama cada frame (opcional, si quieres lógica por frame)
    virtual void Update(float deltaTime) {}

    // Se llama cada frame para dibujar la escena
    virtual void Draw(Shader &shader) = 0;
};
