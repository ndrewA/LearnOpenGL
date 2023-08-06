#pragma once

#include <tuple>

template<typename SystemType, typename... DependencyTypes>
struct SystemNode;

template<typename SystemType, typename... DependencyTypes>
struct SystemNode<SystemType, std::tuple<DependencyTypes...>>
{
    using system = SystemType;
    using dependencies = std::tuple<DependencyTypes...>;
};