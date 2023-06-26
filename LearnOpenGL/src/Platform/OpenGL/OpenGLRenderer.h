#pragma once

#include <memory>

#include "Renderer/Renderer.h"

class OpenGLRenderer : public Renderer
{
public:
    virtual ~OpenGLRenderer() = default;

    virtual void beginScene() override;
    virtual void endScene() override;

    virtual void submit(const std::shared_ptr<Program>& shader,
                        const std::shared_ptr<VertexArray>& vertexArray,
                        const glm::mat4& transform = glm::mat4(1.0f)) override;
};
