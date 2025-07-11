#pragma once

#include <glad/glad.h>
#include <string>

#include <glm/glm.hpp>

class Shader
{
public:
    Shader(const std::string &vertexPath, const std::string &fragmentPath); // Constructor
    ~Shader();                                                              // Destructor

    void Use() const;                                                     // Activar el shader
    void SetMat4(const std::string &name, const glm::mat4 &matrix) const; // Enviar matriz uniforme

    void SetVec3(const std::string &name, const glm::vec3 &value) const;

    GLuint GetID() const { return ID; } // Acceso al ID del programa

private:
    GLuint ID;

    std::string LoadFile(const std::string &path) const;                    // Leer archivo
    GLuint CompileShader(GLenum type, const char *source) const;            // Compilar shader
    GLuint CreateProgram(const char *vertexSrc, const char *fragSrc) const; // Enlazar programa
};
