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

	virtual const unsigned int getHandle() const = 0;
};