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

void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<BaseDataBuffer>& vertexBuffer, const std::unique_ptr<BufferLayout>& layout)
{
	vertexBuffers.emplace_back(vertexBuffer);

	glBindVertexArray(vertexArrayHandle);
	vertexBuffer->bind();


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, (const void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 32, (const void*)12);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 32, (const void*)24);

	for (const auto& element : layout->getElements()) {
		auto OpenGLDataType = layout->getBackendDataType(element.type);

		static unsigned int index = 0;

		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, element.count, OpenGLDataType, element.normalized, (int)layout->getStride(), (const void*)element.offset);

		++index;
	}
	glBindVertexArray(0);
}

void OpenGLVertexArray::setElementBuffer(const std::shared_ptr<ElementBuffer>& elementBuffer)
{
	this->elementBuffer = elementBuffer;

	glBindVertexArray(vertexArrayHandle);
	elementBuffer->bind();
	glBindVertexArray(0);
}
