#include "OpenGLProgram.h"

#include <string>
#include <memory>
#include <stdexcept>

#include <glad/glad.h>

#include "OpenGLShader.h"

#define UNIFORM_FUNC(func, value) [&](location) { func(location, value); }

OpenGLProgram::OpenGLProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
    : vertexPath(vertexPath), fragmentPath(fragmentPath)
{
    auto vertexShader = std::make_unique<OpenGLShader>(vertexShaderPath, ShaderType::Vertex);
    auto fragmentShader = std::make_unique<OpenGLShader>(fragmentShaderPath, ShaderType::Fragment);

    programHandle = glCreateProgram();

    glAttachShader(programHandle, vertexShader->getHandle());
    glAttachShader(programHandle, fragmentShader->getHandle());
    glLinkProgram(programHandle);

    glDetachShader(programHandle, vertexShader->getHandle());
    glDetachShader(programHandle, fragmentShader->getHandle());

    int success;
    glGetProgramiv(programHandle, GL_LINK_STATUS, &success);
    if (!success) {
        int errorLength = 0;
        glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &errorLength);

        std::vector<char> error(errorLength);
        glGetProgramInfoLog(programHandle, errorLength, nullptr, error.data());

        glDeleteProgram(programHandle);

        throw std::runtime_error(error.data());
    }
}

OpenGLProgram::~OpenGLProgram()
{
    glDeleteProgram(programHandle);
}

void OpenGLProgram::bind() const
{
    glUseProgram(programHandle);
}

void OpenGLProgram::unbind() const
{
    glUseProgram(0);
}

void OpenGLProgram::setUniformImpl(const std::string& name, bool value) const
{
    glUniform1i(getLocation(name), (int)value);
    //setUniformWithCheck(name, [&](int location) { glUniform1i(getLocation(name), (int)value); });
}

void OpenGLProgram::setUniformImpl(const std::string& name, int value) const
{
    glUniform1i(getLocation(name), value);
    //setUniformWithCheck(name, [&](int location) { glUniform1i(location, value);  });
}

void OpenGLProgram::setUniformImpl(const std::string& name, float value) const
{
    glUniform1f(getLocation(name), value);
    //setUniformWithCheck(name, [&](int location) { glUniform1f(location, value); });
}

void OpenGLProgram::setUniformImpl(const std::string& name, const glm::mat4& matrix) const
{
    glUniformMatrix4fv(getLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    //setUniformWithCheck(name, [&](int location) { glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix)); });
}

void OpenGLProgram::setUniformImpl(const std::string& name, const glm::vec3& vector) const
{
    glUniform3f(getLocation(name), vector.x, vector.y, vector.z);
    //setUniformWithCheck(name, [&](int location) { glUniform3f(location, vector.x, vector.y, vector.z); });
}

void OpenGLProgram::setUniformImpl(const std::string& name, const glm::vec4& vector) const
{
    glUniform4f(getLocation(name), vector.x, vector.y, vector.z, vector.w);
    //setUniformWithCheck(name, [&](int location) { glUniform4f(getLocation(name), vector.x, vector.y, vector.z, vector.w);});
}

int OpenGLProgram::getLocation(const std::string& name) const
{
    if (uniformLocationsCache.find(name) != uniformLocationsCache.end())
        return uniformLocationsCache.at(name);

    int location = glGetUniformLocation(programHandle, name.c_str());

    //if (location == -1) 
    //    throw std::exception(("Uniform " + name + " not found!").c_str());

    return uniformLocationsCache[name] = location;
}