#include "Mesh.h"
#include <glad/glad.h>

Mesh::Mesh(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec3> &normals)
    : vertexCount(vertices.size())
{
    setupMesh(vertices, normals);
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO_positions);
    glDeleteBuffers(1, &VBO_normals);
}

void Mesh::setupMesh(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec3> &normals)
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // VBO para posiciones
    glGenBuffers(1, &VBO_positions);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_positions);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glEnableVertexAttribArray(0);

    // VBO para normales
    glGenBuffers(1, &VBO_normals);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_normals);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Mesh::Draw() const
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);
}
