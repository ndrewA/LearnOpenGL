#pragma once

#include <string>

class Shader
{
public:
	Shader(const std::string vertexPath, const std::string shaderPath);
	~Shader();

	void use() const;

	void setBool(const std::string name, bool value) const;
	void setInt(const std::string name, int value) const;
	void setFloat(const std::string name, float value) const;

private:
	std::string getShaderString(const std::string path) const;
	unsigned int makeShader(const std::string shaderPath, const unsigned int shaderType) const;

private:
	std::string vertexPath;
	std::string fragmentPath;
	unsigned int id;
};

