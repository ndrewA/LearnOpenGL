#pragma once

#include "NodeMetafunctions.h"
#include "SystemNode.h"

template <typename SystemNode, typename AllSystemNodes>
struct Node
{
    using system = typename SystemNode::system;
    static constexpr size_t id = IndexOf_v<SystemNode, AllSystemNodes>;
    static constexpr auto dependencies =
        makeDependencies<system, typename SystemNode::dependencies, AllSystemNodes>
            (std::make_index_sequence<std::tuple_size_v<typename SystemNode::dependencies>>{});
};

template <typename SystemNodes>
struct TransformToNodes;

template <typename... SystemNodes>
struct TransformToNodes<std::tuple<SystemNodes...>>
{
    using type = std::tuple<Node<SystemNodes, std::tuple<SystemNodes...>>...>;
};

template <typename SystemNodes>
using TransformToNodes_t = typename TransformToNodes<SystemNodes>::type;