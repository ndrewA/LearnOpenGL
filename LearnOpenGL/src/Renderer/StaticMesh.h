#pragma once

#include "Mesh.h"

class StaticMesh : public Mesh
{
public:
    ~StaticMesh() override = default;

    const std::vector<Vertex>& getVertices() const override { return vertices; }
    const std::vector<unsigned int>& getIndices() const override { return indices; }
    const Material& getMaterial() const override { return material; }

    void setVertices(const std::vector<Vertex>& vertices) override { this->vertices = vertices; }
    void setIndices(const std::vector<unsigned int>& indices) override { this->indices = indices; }
    void setMaterial(const Material& material) override { this->material = material; }

private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    Material material;
};