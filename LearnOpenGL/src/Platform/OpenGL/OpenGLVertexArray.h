#pragma once

#include <vector>

#include "Renderer/VertexArray.h"

class OpenGLVertexArray : public VertexArray
{
public:
	OpenGLVertexArray();

	void bind() const override;
	void unbind() const override;

	void addVertexBuffer(std::shared_ptr<BaseDataBuffer> vertexBuffer, std::shared_ptr<BufferLayout> layout) override;
	void setElementBuffer(std::shared_ptr<ElementBuffer> elementBuffer) override;

private:
	unsigned int vertexArrayHandle;

	unsigned int index = 0;

	std::vector<std::shared_ptr<BaseDataBuffer>> vertexBuffers;
	std::shared_ptr<BaseDataBuffer> elementBuffer;
};