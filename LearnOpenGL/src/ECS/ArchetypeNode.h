#pragma once

#include <memory>

#include "Archetype.h"

class ArchetypeNode 
{
public:
    using NodePtr = std::shared_ptr<ArchetypeNode>;
    
    template<typename CompoentType>
    void addEdge(NodePtr node) { edges.insert(ComponentTypeTag<ComponentType>::index, node); }

    template<typename CompoentType>
    NodePtr getEdge() { return edges.get(ComponentTypeTag<ComponentType>::index); }

    const std::vector<Entity>& getEntities() const { return archetype.getEntities(); }

private:
    Archetype archetype;
    SparseSet<NodePtr> edges;
};
