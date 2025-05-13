#pragma once
#include <string>
#include <vector>
#include "Mesh.h"

class Model
{
public:
    Model(const std::string &path);
    void Draw() const;

private:
    std::vector<Mesh> meshes;
    void loadModel(const std::string &path);
};
