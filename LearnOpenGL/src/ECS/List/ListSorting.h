#pragma once

#include <type_traits>
#include <string_view>

#include "List.h"

namespace ListUtils
{
    template <typename... Ts>
    struct Concat;

    template <typename... Ts, typename... Us>
    struct Concat<List<Ts...>, List<Us...>> 
    {
        using type = List<Ts..., Us...>;
    };

    template <typename... Ts>
    struct Append;

    template <typename... Ts, typename T>
    struct Append<List<Ts...>, T> 
    {
        using type = List<Ts..., T>;
    };

    template <typename T>
    constexpr auto typeName() 
    {
        std::string_view name = "Error: unsupported compiler", prefix, suffix;
#ifdef __clang__
        name = __PRETTY_FUNCTION__;
        prefix = "auto type_name() [T = ";
        suffix = "]";
#elif defined(__GNUC__)
        name = __PRETTY_FUNCTION__;
        prefix = "constexpr auto type_name() [with T = ";
        suffix = "]";
#elif defined(_MSC_VER)
        name = __FUNCSIG__;
        prefix = "auto __cdecl type_name<";
        suffix = ">(void)";
#else
        static_assert(false, "Unsupported compiler!");
#endif
        name.remove_prefix(prefix.size());
        name.remove_suffix(suffix.size());
        return name;
    }

    template <typename T, typename U>
    static constexpr bool isSmaller()
    {
        return typeName<T>() < typeName<U>();
    }

    template <typename Pivot, typename List, template <typename, typename> class Condition>
    struct Partition;

    template <typename Pivot, template <typename, typename> class Condition>
    struct Partition<Pivot, List<>, Condition> 
    {
        using type = List<>;
    };

    template <typename Pivot, typename Head, typename... Tail, template <typename, typename> class Condition>
    struct Partition<Pivot, List<Head, Tail...>, Condition> 
    {
        using type = typename std::conditional_t<
            Condition<Pivot, Head>::value,
            typename Append<typename Partition<Pivot, List<Tail...>, Condition>::type, Head>::type,
            typename Partition<Pivot, List<Tail...>, Condition>::type
        >;
    };

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

    template <typename List>
    struct QuickSort;

    template <typename Pivot, typename... Tail>
    struct QuickSort<List<Pivot, Tail...>>
    {

        using LowerPartition = typename Partition<Pivot, List<Tail...>, Less>::type;
        using UpperPartition = typename Partition<Pivot, List<Tail...>, Greater>::type;

        using SortedLowerPartition = typename QuickSort<LowerPartition>::type;
        using SortedUpperPartition = typename QuickSort<UpperPartition>::type;

        using type = typename Concat<
            typename Append<SortedLowerPartition, Pivot>::type,
            SortedUpperPartition
        >::type;
    };

    template <>
    struct QuickSort<List<>>
    {
        using type = List<>;
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
using QuickSort_t = ListUtils::QuickSort<List<Ts...>>::type;

template<typename... Ts>
struct Identifier
{
    inline static size_t value = ListUtils::StaticTypeIndex::get<QuickSort_t<Ts...>>();
};
