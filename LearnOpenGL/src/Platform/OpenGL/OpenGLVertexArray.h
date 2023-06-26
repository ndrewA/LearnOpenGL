#pragma once

#include <vector>

#include "Renderer/VertexArray.h"

class OpenGLVertexArray : public VertexArray
{
public:
	OpenGLVertexArray();

	void bind() const override;
	void unbind() const override;

	void addVertexBuffer(const std::shared_ptr<BaseDataBuffer>& vertexBuffer, const std::unique_ptr<BufferLayout>& layout) override;
	void setElementBuffer(const std::shared_ptr<ElementBuffer>& elementBuffer) override;

private:
	unsigned int vertexArrayHandle;

	std::vector<std::shared_ptr<BaseDataBuffer>> vertexBuffers;
	std::shared_ptr<BaseDataBuffer> elementBuffer;
};