#include "OpenGLElementBuffer.h"

#include <glad/glad.h>

OpenGLElementBuffer::OpenGLElementBuffer(const std::vector<unsigned int>& data)
{
	glGenBuffers(1, &elementHandle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementHandle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(data[0]), &data[0], GL_STATIC_DRAW);
}

OpenGLElementBuffer::~OpenGLElementBuffer()
{
	glDeleteBuffers(1, &elementHandle);
}

void OpenGLElementBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementHandle);
}

void OpenGLElementBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
