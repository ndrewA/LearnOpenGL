#pragma once

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	virtual ~Shader() = default;

	virtual void bind() const = 0;
	virtual void unbind() const = 0;

	template<typename T>
	void setUniform(const std::string& name, const T& value) { setUniformImpl(name, value); }

protected:
	virtual void setUniformImpl(const std::string& name, bool value) const = 0;
	virtual void setUniformImpl(const std::string& name, int value) const = 0;
	virtual void setUniformImpl(const std::string& name, float value) const = 0;
	virtual void setUniformImpl(const std::string& name, const glm::mat4& matrix) const = 0;
	virtual void setUniformImpl(const std::string& name, const glm::vec3& vector) const = 0;
	virtual void setUniformImpl(const std::string& name, const glm::vec4& vector) const = 0;
};