#pragma once

#include "TupleUtils.h"
#include "TupleComparator.h"

namespace
{
    template <typename Pivot, typename T>
    struct Less
    {
        static constexpr bool value = isSmaller<T, Pivot>();
    };

    template <typename Pivot, typename T>
    struct Greater
    {
        static constexpr bool value = !isSmaller<T, Pivot>();
    };

    template <typename Pivot, typename Tuple, template <typename, typename> class Condition>
    struct Partition;

    template <typename Pivot, template <typename, typename> class Condition>
    struct Partition<Pivot, std::tuple<>, Condition>
    {
        using type = std::tuple<>;
    };

    template <typename Pivot, typename Head, typename... Tail, template <typename, typename> class Condition>
    struct Partition<Pivot, std::tuple<Head, Tail...>, Condition>
    {
        using type = typename std::conditional_t<
            Condition<Pivot, Head>::value,
            typename Append<typename Partition<Pivot, std::tuple<Tail...>, Condition>::type, Head>::type,
            typename Partition<Pivot, std::tuple<Tail...>, Condition>::type
        >;
    };

    template <typename... Ts>
    struct QuickSort
    {
        using type = typename QuickSort<std::tuple<Ts...>>::type;
    };

    template <typename Pivot, typename... Tail>
    struct QuickSort<std::tuple<Pivot, Tail...>>
    {

        using LowerPartition = typename Partition<Pivot, std::tuple<Tail...>, Less>::type;
        using UpperPartition = typename Partition<Pivot, std::tuple<Tail...>, Greater>::type;

        using SortedLowerPartition = typename QuickSort<LowerPartition>::type;
        using SortedUpperPartition = typename QuickSort<UpperPartition>::type;

        using type = typename Concat<
            typename Append<SortedLowerPartition, Pivot>::type,
            SortedUpperPartition
        >::type;
    };

    template <>
    struct QuickSort<std::tuple<>>
    {
        using type = std::tuple<>;
    };

    struct StaticTypeIndex
    {
        inline static size_t counter = 0;

        template<typename T>
        static size_t get()
        {
            static size_t value = counter++;
            return value;
        }
    };
}

template <typename... Ts>
using QuickSort_t = typename QuickSort<Ts...>::type;

template<typename... Ts>
struct Identifier
{
    inline static size_t value = StaticTypeIndex::get<QuickSort_t<Ts...>>();
};