#include "OpenGLVertexArray.h"

#include <glad/glad.h>

OpenGLVertexArray::OpenGLVertexArray()
{
	glGenVertexArrays(1, &vertexArrayHandle);
}

void OpenGLVertexArray::bind() const
{
	glBindVertexArray(vertexArrayHandle);
}

void OpenGLVertexArray::unbind() const
{
	glBindVertexArray(0);
}

void OpenGLVertexArray::addVertexBuffer(std::shared_ptr<BaseDataBuffer> vertexBuffer, std::shared_ptr<BufferLayout> layout)
{
	vertexBuffers.emplace_back(vertexBuffer);

	glBindVertexArray(vertexArrayHandle);
	vertexBuffer->bind();

	for (const auto& element : layout->getElements()) {
		auto OpenGLDataType = layout->getBackendDataType(element.type);

		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, element.count, OpenGLDataType, element.normalized, (int)layout->getStride(), (const void*)element.offset);

		++index;
	}
	glBindVertexArray(0);
}

void OpenGLVertexArray::setElementBuffer(std::shared_ptr<ElementBuffer> elementBuffer)
{
	this->elementBuffer = elementBuffer;

	glBindVertexArray(vertexArrayHandle);
	elementBuffer->bind();
	glBindVertexArray(0);
}
