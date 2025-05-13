#pragma once
#include <vector>
#include <glm/glm.hpp>

class Mesh
{
public:
    Mesh(const std::vector<glm::vec3> &vertices);
    ~Mesh();

    void Draw() const;

private:
    unsigned int VAO, VBO;
    int vertexCount;

    void setupMesh(const std::vector<glm::vec3> &vertices);
};
