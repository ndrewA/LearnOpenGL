#pragma once

#include <memory>

#include "Buffer.h"
#include "BufferLayout.h"

class VertexArray
{
public:
	virtual ~VertexArray() = default;

	virtual void bind() const = 0;
	virtual void unbind() const = 0;

	virtual void addVertexBuffer(std::shared_ptr<BaseDataBuffer> vertexBuffer, std::shared_ptr<BufferLayout> layout) = 0;
	virtual void setElementBuffer(std::shared_ptr<ElementBuffer> elementBuffer) = 0;
};