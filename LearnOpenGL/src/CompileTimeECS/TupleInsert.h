#pragma once

#include <tuple>
#include <utility>

#include "TupleComparator.h"

namespace
{
    template <typename Tuple, size_t... Is>
    constexpr auto getFirstHalf(Tuple tuple, std::index_sequence<Is...>) 
    {
        return std::make_tuple(std::get<Is>(tuple)...);
    }

    template <typename Tuple, size_t... Is>
    constexpr auto getSecondHalf(Tuple tuple, std::index_sequence<Is...>) 
    {
        constexpr size_t offset = std::tuple_size<Tuple>::value / 2;
        return std::make_tuple(std::get<Is + offset>(tuple)...);
    }

    template <typename T, typename Tuple>
    auto binarySearchInsert(Tuple tuple, T value, std::index_sequence<>)
    {
        return std::make_tuple(value);
    }

    template <typename T, typename Tuple>
    auto binarySearchInsert(Tuple tuple, T value, std::index_sequence<0>)
    {
        using FirstType = std::tuple_element_t<0, Tuple>;
        if constexpr (isSmaller<T, FirstType>())
            return std::tuple_cat(std::make_tuple(value), tuple);
        else
            return std::tuple_cat(tuple, std::make_tuple(value));
    }

    template <typename T, typename Tuple, size_t... Is>
    auto binarySearchInsert(Tuple tuple, T value, std::index_sequence<Is...>)
    {
        constexpr size_t N = sizeof...(Is);
        constexpr size_t middle = N / 2;
        using MiddleType = std::tuple_element_t<middle, Tuple>;

        auto firstHalf = getFirstHalf(tuple, std::make_index_sequence<middle>{});
        auto secondHalf = getSecondHalf(tuple, std::make_index_sequence<N - middle>{});

        if constexpr (isSmaller<T, MiddleType>())
            return std::tuple_cat(binarySearchInsert(firstHalf, value), secondHalf);
        else
            return std::tuple_cat(firstHalf, binarySearchInsert(secondHalf, value));
    }
}

template <typename T, typename Tuple>
auto binarySearchInsert(Tuple tuple, T value)
{
    return binarySearchInsert(tuple, value, std::make_index_sequence<std::tuple_size<Tuple>::value>{});
}