#include "Model.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>

Model::Model(const std::string &path)
{
    loadModel(path);
}

void Model::Draw() const
{
    for (const auto &mesh : meshes)
        mesh.Draw();
}

void Model::loadModel(const std::string &path)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenNormals);

    if (!scene || !scene->HasMeshes())
    {
        std::cerr << "Error cargando modelo: " << importer.GetErrorString() << std::endl;
        return;
    }

    aiMesh *mesh = scene->mMeshes[0];
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;

    for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
    {
        aiVector3D pos = mesh->mVertices[i];
        aiVector3D norm = mesh->mNormals[i];

        vertices.emplace_back(pos.x, pos.y, pos.z);
        normals.emplace_back(norm.x, norm.y, norm.z);
    }

    meshes.emplace_back(vertices, normals);
}
