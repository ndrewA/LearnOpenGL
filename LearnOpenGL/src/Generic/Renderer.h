#pragma once

#include "VertexArray.h"
#include "Buffer.h"
#include "Program.h"

struct Color
{
	float r, g, b, a;
};

class Renderer
{
public:
	virtual ~Renderer() = default;

	virtual void clear() const = 0;
	virtual void setClearColor(const Color& color) = 0;

	virtual void draw(const std::shared_ptr<VertexArray>& vertexArray,  const std::shared_ptr<ElementBuffer>& elementBuffer, const std::shared_ptr<Program>& program) const = 0;
};