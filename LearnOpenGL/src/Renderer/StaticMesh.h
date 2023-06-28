#pragma once

#include "Mesh.h"

class StaticMesh : public Mesh
{
public:
    StaticMesh(const std::vector<Vertex>& certices, const std::vector<unsigned int>& indices, const Material& material)
        : vertices(vertices), indices(indices), material(material) { }
    ~StaticMesh() override = default;

    const std::vector<Vertex>& getVertices() const override { return vertices; }
    const std::vector<unsigned int>& getIndices() const override { return indices; }
    const Material& getMaterial() const override { return material; }

private:
    const std::vector<Vertex> vertices;
    const std::vector<unsigned int> indices;
    const Material material;
};