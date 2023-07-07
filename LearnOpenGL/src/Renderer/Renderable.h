#pragma once

#include "Material.h"
#include "Mesh.h"

class Renderable {
public:
    virtual ~Renderable() = default;
    virtual const Mesh& getMesh() const = 0;
    virtual const Material& getMaterial() const = 0;
    virtual const glm::mat4& getTransform() const = 0;
};