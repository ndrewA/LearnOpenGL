#pragma once

#include <string>

#include "Renderer/Shader.h"

class OpenGLShader : public Shader
{
public:
	OpenGLShader(const std::string& shaderPath, ShaderType shaderType);
	~OpenGLShader() override;

	unsigned int getHandle() const override { return shaderHandle; }

private:
	char* getShaderString(const std::string& shaderPath) const;

private:
	unsigned int shaderHandle;
};

