#pragma once

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	Shader(const std::string vertexPath, const std::string shaderPath);
	~Shader();

	void use() const;

	void setBool(const std::string name, bool value) const;
	void setInt(const std::string name, int value) const;
	void setFloat(const std::string name, float value) const;
	void setMat4(const std::string name, const glm::mat4 matrix) const;
	void setVec3(const std::string name, const glm::vec3 vector) const;

private:
	std::string getShaderString(const std::string path) const;
	unsigned int makeShader(const std::string shaderPath, const unsigned int shaderType) const;
	int getLocation(const std::string name) const;

private:
	std::string vertexPath;
	std::string fragmentPath;
	unsigned int id;
};

