#pragma once

#include <stdexcept>

#include "ArchetypeGraph.h"
#include "SparseSet.h"

class ArchetypeGraphManager
{
public:
    template<typename ComponentType>
    void addComponent(Entity entity)
    {
        if (entity.index >= entityToNode.size())
            entityToNode.resize(entity.index + 1, -1);

        size_t oldNodeIndex = entityToNode[entity.index];

        if (oldNodeIndex != -1) {
            size_t newNodeIndex = graph.getEdgeIndexFromNode<ComponentType>(oldNodeIndex);;

            graph.removeEntityFromNode(oldNodeIndex, entity);
            graph.addEntityToNode(newNodeIndex, entity);
        }
        else {
            size_t newNodeIndex = graph.findNode<ComponentType>();
            graph.addEntityToNode(newNodeIndex, entity);
        }
        entityToNode[entity.index] = newNodeIndex;
    }

    template<typename ComponentType>
    void removeComponent(Entity entity)
    {
        size_t nodeIndex = entityToNode[entity.index];
        graph.removeEntityFromNode(nodeIndex, entity);
        entityToNode[entity.index] = -1;
    }

    template<typename... ComponentTypes>
    const std::vector<Entity>& getEntities() const
    {
        return graph.getEntitiesfromNode<ComponentTypes...>();
    }

private:
    static inline ArchetypeGraph graph;
    static inline std::vector<size_t> entityToNode;
};