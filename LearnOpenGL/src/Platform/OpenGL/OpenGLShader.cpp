#include "OpenGLShader.h"

#include <glad/glad.h>

#include <iostream>
#include <string>
#include <fstream>
#include <iterator>

#define UNIFORM_FUNC(func, value) [&](location) { func(location, value); }

OpenGLShader::OpenGLShader(const std::string& vertexPath, const std::string& fragmentPath)
    : vertexPath(vertexPath), fragmentPath(fragmentPath)
{
    unsigned int vertexShader = makeShader(vertexPath, GL_VERTEX_SHADER);
    unsigned int fragmentShader = makeShader(fragmentPath, GL_FRAGMENT_SHADER);
    makeProgram(vertexShader, fragmentShader);
}

OpenGLShader::~OpenGLShader()
{
    glDeleteProgram(programHandle);
}

void OpenGLShader::makeProgram(const unsigned int vertexShader, const unsigned int fragmentShader)
{
    programHandle = glCreateProgram();

    glAttachShader(programHandle, vertexShader);
    glAttachShader(programHandle, fragmentShader);
    glLinkProgram(programHandle);

    glDetachShader(programHandle, vertexShader);
    glDetachShader(programHandle, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    int succes;
    const unsigned int errorLength = 512;
    char error[errorLength];

    glGetProgramiv(programHandle, GL_LINK_STATUS, &succes);
    if (!succes) {
        glGetProgramInfoLog(programHandle, errorLength, nullptr, error);
        throw std::runtime_error(error);
    }
}

unsigned int OpenGLShader::makeShader(const std::string& shaderPath, const unsigned int shaderType) const
{
    unsigned int shader = glCreateShader(shaderType);

    const std::string shaderString = getShaderString(shaderPath);
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
        const std::string shaderTypeString = GL_VERTEX_SHADER ? "vertex" : "fragment";
        throw std::runtime_error(shaderTypeString + " shader compilation failed: " + (std::string)infoLog);
    }
    return shader;
}

std::string OpenGLShader::getShaderString(const std::string path) const
{
    std::fstream file(path);
    if (!file.is_open())
        throw std::runtime_error("cannot open file : " + path);
    std::string shaderString(std::istreambuf_iterator<char>{file}, {});
    return shaderString;
}

void OpenGLShader::bind() const
{
    glUseProgram(programHandle);
}

void OpenGLShader::unbind() const
{
    glUseProgram(0);
}

void OpenGLShader::setUniformImpl(const std::string& name, const bool value) const
{
    glUniform1i(getLocation(name), (int)value);
    //setUniformWithCheck(name, [&](int location) { glUniform1i(getLocation(name), (int)value); });
}

void OpenGLShader::setUniformImpl(const std::string& name, const int value) const
{
    glUniform1i(getLocation(name), value);
    //setUniformWithCheck(name, [&](int location) { glUniform1i(location, value);  });
}

void OpenGLShader::setUniformImpl(const std::string& name, const float value) const
{
    glUniform1f(getLocation(name), value);
    //setUniformWithCheck(name, [&](int location) { glUniform1f(location, value); });
}

void OpenGLShader::setUniformImpl(const std::string& name, const glm::mat4& matrix) const
{ 
    glUniformMatrix4fv(getLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    //setUniformWithCheck(name, [&](int location) { glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix)); });
}

void OpenGLShader::setUniformImpl(const std::string& name, const glm::vec3& vector) const
{
    glUniform3f(getLocation(name), vector.x, vector.y, vector.z);
    //setUniformWithCheck(name, [&](int location) { glUniform3f(location, vector.x, vector.y, vector.z); });
}

void OpenGLShader::setUniformImpl(const std::string& name, const glm::vec4& vector) const
{
    glUniform4f(getLocation(name), vector.x, vector.y, vector.z, vector.w);
    //setUniformWithCheck(name, [&](int location) { glUniform4f(getLocation(name), vector.x, vector.y, vector.z, vector.w);});
}

int OpenGLShader::getLocation(const std::string& name) const
{
    if (locationsCache.find(name) != locationsCache.end())
        return locationsCache[name];

    int location = glGetUniformLocation(programHandle, name.c_str());

    //if (location == -1) 
    //    throw std::exception(("Uniform " + name + " not found!").c_str());

    return locationsCache[name] = location;
}