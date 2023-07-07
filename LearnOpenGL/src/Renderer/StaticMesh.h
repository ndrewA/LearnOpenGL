#pragma once

#include "Mesh.h"

class StaticMesh : public Mesh
{
public:
    StaticMesh(const std::vector<Vertex>& certices, const std::vector<unsigned int>& indices, const Material& material)
        : vertices(vertices), indices(indices) { }
    ~StaticMesh() override = default;

    const std::vector<Vertex>& getVertices() const override { return vertices; }
    const std::vector<unsigned int>& getIndices() const override { return indices; }

private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
};