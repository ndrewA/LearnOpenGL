#include "Shader.h"

#include <glad/glad.h>

#include <iostream>
#include <string>
#include <fstream>
#include <iterator>

Shader::Shader(const std::string vertexPath, const std::string fragmentPath)
    : vertexPath(vertexPath), fragmentPath(fragmentPath)
{
    unsigned int vertexShader = makeShader(vertexPath, GL_VERTEX_SHADER);
    unsigned int fragmentShader = makeShader(fragmentPath, GL_FRAGMENT_SHADER);
    id = glCreateProgram();

    glAttachShader(id, vertexShader);
    glAttachShader(id, fragmentShader);
    glLinkProgram(id);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    int succes;
    const unsigned int infoLogLength = 512;
    char infoLog[infoLogLength];

    glGetProgramiv(id, GL_LINK_STATUS, &succes);
    if (!succes) {
        glGetProgramInfoLog(id, infoLogLength, nullptr, infoLog);
        std::cout << "program failed: " << infoLog << '\n';
        __debugbreak();
    }
}

Shader::~Shader()
{
    glDeleteProgram(id);
}

void Shader::use() const
{
    glUseProgram(id);
}

void Shader::setBool(const std::string name, bool value) const
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void Shader::setInt(const std::string name, int value) const
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setFloat(const std::string name, float value) const
{
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setMat4(const std::string name, const glm::mat4 matrix) const
{
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

std::string Shader::getShaderString(const std::string path) const
{
    std::fstream file(path);
    if (!file.is_open())
    {
        std::cout << "cannot open file\n";
        __debugbreak();
    }
    std::string shaderString(std::istreambuf_iterator<char>{file}, {});
    return shaderString;
}

unsigned int Shader::makeShader(const std::string shaderPath, const unsigned int shaderType) const
{
    unsigned int shader = glCreateShader(shaderType);

    std::string shaderString = getShaderString(shaderPath);
    char* shaderSource = new char[shaderString.length() + 1];
    strcpy(shaderSource, shaderString.c_str());
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    int succes;
    const unsigned int infoLogLength = 512;
    char infoLog[infoLogLength];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &succes);

    if (!succes) {
        glGetShaderInfoLog(shader, infoLogLength, nullptr, infoLog);
        std::cout << (shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment")
            << " shader compilation failed: " << infoLog << '\n';
        __debugbreak();
    }
    return shader;
}