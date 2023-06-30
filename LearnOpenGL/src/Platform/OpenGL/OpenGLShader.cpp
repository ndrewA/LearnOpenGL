#include "OpenGLShader.h"

#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include <stdexcept>

#include <glad/glad.h>

OpenGLShader::OpenGLShader(const std::string& shaderPath, ShaderType type)
{
    shaderHandle = (type == ShaderType::Vertex) ? 
                 glCreateShader(GL_VERTEX_SHADER) : glCreateShader(GL_FRAGMENT_SHADER);

    char* shaderSource = getShaderString(shaderPath);
   
    glShaderSource(shaderHandle, 1, &shaderSource, nullptr);
    glCompileShader(shaderHandle);

    delete[] shaderSource;

    int success;
    glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &success);

    if (!success) {
        int errorLength = 0;
        glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &errorLength);

        std::vector<char> error(errorLength);
        glGetShaderInfoLog(shaderHandle, errorLength, nullptr, error.data());

        glDeleteShader(shaderHandle);

        throw std::runtime_error(error.data());
    }
}

OpenGLShader::~OpenGLShader()
{
    glDeleteShader(shaderHandle);
}

char* OpenGLShader::getShaderString(const std::string& shaderPath) const
{
    std::fstream file(shaderPath);

    if (!file.is_open()) {
        glDeleteShader(shaderHandle);
        throw std::runtime_error("cannot open file : " + shaderPath);
    }

    std::string shaderString(std::istreambuf_iterator<char>{file}, {});

    char* cShaderString = new char[shaderString.length() + 1];
    strcpy(cShaderString, shaderString.c_str());

    return cShaderString;
}
