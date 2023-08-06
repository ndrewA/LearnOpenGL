#pragma once

#include <tuple>
#include <stdexcept>

#include "Node.h"
#include "ConstexprQueue.h"

template <typename Nodes>
class TopologicalIndexSorter
{
public:
    consteval TopologicalIndexSorter()
    {
        inDegrees = computeInDegrees<Nodes>();
        fillZeroInDegreeQueue();
        processNodes(std::make_index_sequence<std::tuple_size_v<Nodes>>{});
        if (count != 0)
            throw std::logic_error("There exists a cycle in the graph");
    }

    consteval auto getSortedIndices() const
    {
        return sortedNodes;
    }

private:
    template <typename Dependencies>
    consteval void processDependencies(const Dependencies& dependencies)
    {
        for (const auto dependency : dependencies)
            if (--inDegrees[dependency] == 0)
                queue.push(dependency);
    }

    template <size_t Index>
    consteval void processNode(size_t target)
    {
        if (Index != target)
            return;

        const auto& dependencies = std::tuple_element_t<Index, Nodes>::dependencies;
        processDependencies(dependencies);
    }

    template <size_t... I>
    consteval void processNodes(std::index_sequence<I...>)
    {
        if (queue.empty())
            return;

        size_t node = queue.pop();
        sortedNodes[--count] = node;

        (processNode<I>(node), ...);

        processNodes(std::index_sequence<I...>{});
    }

    consteval void fillZeroInDegreeQueue()
    {
        for (size_t i = 0; i < inDegrees.size(); ++i)
            if (inDegrees[i] == 0)
                queue.push(i);
    }

    template <typename NodeTuple, size_t... I>
    consteval auto computeInDegrees(std::index_sequence<I...>)
    {
        std::array<size_t, sizeof...(I)> inDegrees = { 0 };
        ((void)([&]() {
            for (auto dependency : std::tuple_element_t<I, NodeTuple>::dependencies)
                ++inDegrees[dependency];
            }()), ...);

        return inDegrees;
    }

    template <typename NodeTuple>
    consteval auto computeInDegrees()
    {
        return computeInDegrees<NodeTuple>
            (std::make_index_sequence<std::tuple_size_v<NodeTuple>>{});
    }

private:
    std::array<size_t, std::tuple_size_v<Nodes>> inDegrees;
    ConstexprQueue<size_t, std::tuple_size_v<Nodes>> queue;
    std::array<size_t, std::tuple_size_v<Nodes>> sortedNodes;
    size_t count = std::tuple_size_v<Nodes>;
};