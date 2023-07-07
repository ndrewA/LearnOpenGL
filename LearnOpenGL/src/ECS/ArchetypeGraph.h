#pragma once

#include "ArchetypeNode.h"
#include "Familiy.h"

class ArchetypeGraph
{
public:
    using NodePtr = std::shared_ptr<ArchetypeNode>;

    ArchetypeGraph()
        : baseNode(std::make_shared<ArchetypeNode>()) { }

    template<typename... ComponentTypes>
    NodePtr getOrCreateNode()
    {
        size_t key = Family<ComponentTypes>::type();

        if (nodes.has(key)) 
            return nodes.get(key);

        nodes.insert(key, std::make_shared<ArchetypeNode>());
        return nulltpr;
    }

private:
    SparseSet<NodePtr> nodes;
    NodePtr baseNode;
};