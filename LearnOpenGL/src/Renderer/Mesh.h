#pragma once

#include "Material.h"

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

class Mesh
{
public:
    virtual ~Mesh() = default;

    virtual const std::vector<Vertex>& getVertices() const = 0;
    virtual const std::vector<unsigned int>& getIndices() const = 0;
    virtual const Material& getMaterial() const = 0;

    virtual void setVertices(const std::vector<Vertex>& vertexArray) = 0;
    virtual void setIndices(const std::vector<unsigned int>& elementBuffer) = 0;
    virtual void setMaterial(const Material& material) = 0;
};