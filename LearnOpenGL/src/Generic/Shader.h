#pragma once

enum class ShaderType
{
	Vertex,
	Fragment
};

class Shader
{
public:	
	virtual ~Shader() = default;

	virtual unsigned int getHandle() const = 0;
};