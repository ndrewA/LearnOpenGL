#pragma once

#include "Renderer/Buffer.h"

#include <glad/glad.h>

template <typename T>
class OpenGLVertexBuffer : public VertexBuffer<T>
{
public:
	OpenGLVertexBuffer(const std::vector<T>& data)
	{
		glGenBuffers(1, &vertexHandle);
		glBindBuffer(GL_ARRAY_BUFFER, vertexHandle);
		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(data[0]), &data[0], GL_STATIC_DRAW);
	}

	~OpenGLVertexBuffer() override
	{
		glDeleteBuffers(1, &vertexHandle);
	}

	void bind() const override
	{
		glBindBuffer(GL_ARRAY_BUFFER, vertexHandle);
	}

	void unbind() const override
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

private:
	unsigned int vertexHandle;
};