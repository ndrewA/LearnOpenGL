#pragma once

#include "TopologicalIndexSorter.h"

template <typename SystemNodes>
consteval auto topologicalSortIndices()
{
    using Nodes = TransformToNodes_t<SystemNodes>;
    TopologicalIndexSorter<Nodes> sorter;
    return sorter.getSortedIndices();
}

template <typename Nodes, auto IndicesArray, typename IndexSequence>
struct ExtractSystems;

template <typename Nodes, auto IndicesArray, size_t... I>
struct ExtractSystems<Nodes, IndicesArray, std::index_sequence<I...>>
{
    using type = std::tuple<typename std::tuple_element_t<IndicesArray[I], Nodes>::system...>;
};

template <typename Nodes, auto IndicesArray>
using ExtractSystems_t = ExtractSystems<Nodes, IndicesArray, std::make_index_sequence<IndicesArray.size()>>::type;

template<typename SystemNodeTuple>
using TopologicallySort_t = ExtractSystems_t<SystemNodeTuple, topologicalSortIndices<SystemNodeTuple>()>;