#pragma once

#include <utility>
#include <tuple>
#include <type_traits>

namespace
{
    template <typename T, typename U>
    auto conditionalTuple(U&& u) 
    {
        if constexpr (!std::is_same_v<T, std::decay_t<U>>)
            return std::make_tuple(std::forward<U>(u));
        else
            return std::tuple<>{};
    }

    template <typename T, typename Tuple, size_t... Is>
    auto removeTypeFromTuple(Tuple tuple, std::index_sequence<Is...>)
    {
        return std::tuple_cat(conditionalTuple<T>(std::get<Is>(tuple))...);
    }
}

namespace
{
    template <typename T, typename... Ts>
    struct RemoveType;

    template <typename T, typename... Ts>
    struct RemoveType<T, T, Ts...> 
    {
        using type = typename RemoveType<T, Ts...>::type;
    };

    template <typename T, typename Head, typename... Ts>
    struct RemoveType<T, Head, Ts...> 
    {
        using type = decltype(std::tuple_cat(std::tuple<Head>{}, typename RemoveType<T, Ts...>::type{}));
    };

    template <typename T>
    struct RemoveType<T> 
    {
        using type = std::tuple<>;
    };
}

template <typename T, typename... Ts>
using RemoveType_t = typename RemoveType<T, Ts...>::type;

template <typename T, typename Tuple>
auto removeTypeFromTuple(Tuple tuple)
{
    return removeTypeFromTuple<T>(tuple, std::make_index_sequence<std::tuple_size<Tuple>::value>{});
}
