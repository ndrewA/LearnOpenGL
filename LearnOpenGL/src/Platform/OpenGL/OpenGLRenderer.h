#pragma once

#include "Generic/Renderer.h"

class OpenGLRenderer : public Renderer
{
public:
	~OpenGLRenderer() override;

	void clear() const override;
	void setClearColor(const Color& color) override;

	void draw(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<ElementBuffer>& elementBuffer, const std::shared_ptr<Program>& program) const override;
};

