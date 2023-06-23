#pragma once

#include <vector>

class BaseDataBuffer {
public:
	virtual ~BaseDataBuffer() = default;

	virtual void bind() const = 0;
	virtual void unbind() const = 0;
};

template <typename T>
class VertexBuffer : public BaseDataBuffer
{
public:
	virtual ~VertexBuffer() = default;

	virtual void bind() const = 0;
	virtual void unbind() const = 0;
};

class ElementBuffer : public BaseDataBuffer
{
public:
	virtual ~ElementBuffer() = default;

	virtual void bind() const = 0;
	virtual void unbind() const = 0;
};