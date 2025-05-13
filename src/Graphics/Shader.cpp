#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath)
{
    std::string vertexCode = LoadFile(vertexPath);
    std::string fragmentCode = LoadFile(fragmentPath);

    ID = CreateProgram(vertexCode.c_str(), fragmentCode.c_str());
}

Shader::~Shader()
{
    glDeleteProgram(ID);
}

void Shader::Use() const
{
    glUseProgram(ID);
}

void Shader::SetMat4(const std::string &name, const glm::mat4 &matrix) const
{
    GLuint location = glGetUniformLocation(ID, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

std::string Shader::LoadFile(const std::string &path) const
{
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

GLuint Shader::CompileShader(GLenum type, const char *source) const
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char info[512];
        glGetShaderInfoLog(shader, 512, nullptr, info);
        std::cerr << "Shader compile error:\n"
                  << info << std::endl;
    }

    return shader;
}

GLuint Shader::CreateProgram(const char *vertexSrc, const char *fragSrc) const
{
    GLuint vert = CompileShader(GL_VERTEX_SHADER, vertexSrc);
    GLuint frag = CompileShader(GL_FRAGMENT_SHADER, fragSrc);

    GLuint program = glCreateProgram();
    glAttachShader(program, vert);
    glAttachShader(program, frag);
    glLinkProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        char info[512];
        glGetProgramInfoLog(program, 512, nullptr, info);
        std::cerr << "Shader link error:\n"
                  << info << std::endl;
    }

    glDeleteShader(vert);
    glDeleteShader(frag);

    return program;
}
