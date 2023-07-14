#pragma once

#include <memory>
#include <stdexcept>

#include "Archetype.h"
#pragma once

#include <memory>
#include <stdexcept>

#include "Archetype.h"

class ArchetypeNode
{
public:
    template<typename ComponentType>
    void addEdge(size_t nodeIndex)
    {
        size_t index = getIndex<ComponentType>();
        if (index >= edges.size())
            edges.resize(index + 1, -1);
        edges[index] = nodeIndex;
    }

    template<typename ComponentType>
    bool hasEdge() const
    {
        size_t index = getIndex<ComponentType>();
        return index < edges.size() && edges[index] != -1;
    }

    template<typename ComponentType>
    size_t getEdgeIndex() const
    {
        if (hasEdge<ComponentType>())
            return edges[getIndex<ComponentType>()];
        throw std::runtime_error("Edge not found!");
    }

    const std::vector<size_t>& getAllEdgeIndices() const { return edges; }

    bool hasEntity(Entity entity) const { return archetype.hasEntity(entity); }
    void addEntity(Entity entity) { archetype.addEntity(entity); }
    void removeEntity(Entity entity) { archetype.removeEntity(entity); }
    const std::vector<Entity>& getEntities() const { return archetype.getEntities(); }

private:
    struct BaseTypeIndex
    {
        inline static size_t counter = 0;
    };

    template <typename ComponentType>
    struct TypeIndex : BaseTypeIndex
    {
        size_t index = counter++;
    };

    template<typename ComponentType>
    size_t getIndex() const
    {
        static TypeIndex<ComponentType> typeIndex;
        return typeIndex.index;
    }

private:
    Archetype archetype;
    std::vector<size_t> edges;
};