#pragma once

#include "ArchetypeNode.h"


class ArchetypeGraph
{
public:
    template<typename ComponentType>
    size_t getEdgeIndexFromNode(size_t nodeIndex)
    {
        if (nodeIndex >= nodes.size())
            throw std::runtime_error("NodeIndex out of bounds!");
        return nodes[nodeIndex]->getEdgeIndex<ComponentType>();
    }

    template<typename ComponentType>
    void addEdgeToNode(size_t fromNodeIndex, size_t toNodeIndex)
    {
        if (fromNodeIndex >= nodes.size() || toNodeIndex >= nodes.size())
            throw std::runtime_error("NodeIndex out of bounds!");

        nodes[fromNodeIndex]->addEdge<ComponentType>(toNodeIndex);
    }

    template<typename ComponentType>
    bool hasEdge(size_t nodeIndex)
    {
        return nodes[nodeIndex]->hasEdge<ComponentType>();
    }

    void addEntityToNode(size_t nodeIndex, Entity entity)
    {
        if (!hasNode(nodeIndex))
            throw std::runtime_error("NodeIndex invalid!");
        nodes[nodeIndex]->addEntity(entity);
    }

    void removeEntityFromNode(size_t nodeIndex, Entity entity)
    {
        nodes[nodeIndex]->removeEntity(entity);
    }

    template<typename... ComponentTypes>
    const std::vector<Entity>& getEntitiesfromNode() const
    {
        size_t nodeIndex = findNode<ComponentTypes...>();
        return nodes[nodeIndex]->getEntities();
    }

private:
    template<typename... ComponentTypes>
    size_t addNode()
    {
        size_t nodeIndex = Identifier<ComponentTypes...>::value;
        if (nodeIndex >= nodes.size())
            nodes.resize(nodeIndex + 1);
        nodes[nodeIndex] = std::make_unique<ArchetypeNode>();
        return nodeIndex;
    }

    bool hasNode(size_t nodeIndex)
    {
        return nodeIndex < nodes.size() && nodes[nodeIndex] != nullptr;
    }

private:
    inline static std::vector<std::unique_ptr<ArchetypeNode>> nodes;
};