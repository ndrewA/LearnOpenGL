#pragma once

#include "Renderer/Program.h"

#include <unordered_map>

class OpenGLProgram : public Program
{
public:
	OpenGLProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	~OpenGLProgram() override;

	void bind() const override;
	void unbind() const override;

protected:
	void setUniformImpl(const std::string& name, const bool value) const override;
	void setUniformImpl(const std::string& name, const int value) const override;
	void setUniformImpl(const std::string& name, const float value) const override;
	void setUniformImpl(const std::string& name, const glm::mat4& matrix) const override;
	void setUniformImpl(const std::string& name, const glm::vec3& vector) const override;
	void setUniformImpl(const std::string& name, const glm::vec4& vector) const override;

private:
	template <typename Func>
	void setUniformWithCheck(const std::string& name, Func setUniformFunc) const
	{
		try {
			setUniformFunc(getLocation(name));
		}
		catch (const std::exception& e) {
			std::cout << e.what();
		}
	}

	int getLocation(const std::string& name) const;

private:
	const std::string vertexPath;
	const std::string fragmentPath;
	unsigned int programHandle;
	mutable std::unordered_map<std::string, int> uniformLocationsCache;
};
