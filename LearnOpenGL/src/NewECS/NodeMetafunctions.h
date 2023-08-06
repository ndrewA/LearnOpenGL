#pragma once

#include <tuple>

#include "SystemNode.h"

template <typename T>
concept IsSystemNode = requires {
    typename T::system;
    typename T::dependencies;
};

template <typename T, typename Tuple>
struct IndexOf;

template <typename T>
struct IndexOf<T, std::tuple<>>
{
    static_assert(!std::is_same_v<T, T>, "Type T not found in tuple!");
};

template <IsSystemNode T, typename... Types>
struct IndexOf<T, std::tuple<T, Types...>>
{
    static constexpr size_t value = 0;
};

template <IsSystemNode T, typename U, typename... Types>
struct IndexOf<T, std::tuple<U, Types...>>
{
    static constexpr size_t value = 1 + IndexOf<T, std::tuple<Types...>>::value;
};

template <typename System, typename Dependencies, typename... Tail>
    requires (!IsSystemNode<System>)
struct IndexOf<System, std::tuple<SystemNode<System, Dependencies>, Tail...>>
{
    static constexpr size_t value = 0;
};

template <typename System1, typename System2, typename Dependencies, typename... Tail>
    requires (!IsSystemNode<System1>)
struct IndexOf<System1, std::tuple<SystemNode<System2, Dependencies>, Tail...>>
{
    static constexpr size_t value = 1 + IndexOf<System1, std::tuple<Tail...>>::value;
};

template <typename T, typename Tuple>
constexpr size_t IndexOf_v = IndexOf<T, Tuple>::value;

template <typename System, typename Dependencies, typename AllSystemNodes, size_t... I>
consteval auto makeDependencies(std::index_sequence<I...>)
{
    return std::array<size_t, sizeof...(I)>
        { IndexOf_v<std::tuple_element_t<I, Dependencies>, AllSystemNodes>... };
}

