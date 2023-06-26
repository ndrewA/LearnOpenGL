#pragma once

#include <memory>

#include "Program.h"
#include "VertexArray.h"

class Renderer
{
public:
    virtual ~Renderer() = default;

    virtual void beginScene() = 0;
    virtual void endScene() = 0;

    virtual void submit(const std::shared_ptr<Program>& shader, 
                        const std::shared_ptr<VertexArray>& vertexArray, 
                        const glm::mat4& transform = glm::mat4(1.0f)) = 0;
};