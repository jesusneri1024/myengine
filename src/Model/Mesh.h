#pragma once
#include <vector>
#include <glm/glm.hpp>

class Mesh
{
public:
    Mesh(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec3> &normals);
    ~Mesh();

    void Draw() const;

private:
    unsigned int VAO, VBO_positions, VBO_normals;
    int vertexCount;

    void setupMesh(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec3> &normals);
};
