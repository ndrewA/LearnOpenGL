#pragma once

#include "FunctionTraits.h"
#include "HasUpdate.h"

template <HasUpdate... SystemTypes>
struct ComponentCollector
{
    using type = decltype(std::tuple_cat(std::declval<typename FunctionTraits<decltype(&SystemTypes::update)>::ArgTypes>()...));
};

template <typename T, typename Tuple>
struct TupleContains;

template <typename T, typename... Us>
struct TupleContains<T, std::tuple<Us...>> : std::disjunction<std::is_same<T, Us>...> { };

template <typename T, typename Tuple>
inline constexpr bool TupleContains_v = TupleContains<T, Tuple>::value;

template <typename Tuple, typename T>
struct AppendIfUnique
{
    using type = std::conditional_t<TupleContains_v<T, Tuple>,
        Tuple, decltype(std::tuple_cat(std::declval<Tuple>(), std::tuple<T>()))>;
};

template <typename Tuple, typename T>
using AppendIfUnique_t = typename AppendIfUnique<Tuple, T>::type;

template <typename TupleWithDuplicate, typename TupleWithUnique = std::tuple<>>
struct UniqueTuple;

template <typename... Ts>
struct UniqueTuple<std::tuple<>, std::tuple<Ts...>>
{
    using type = std::tuple<Ts...>;
};

template <typename... Ts, typename T, typename... Us>
struct UniqueTuple<std::tuple<T, Ts...>, std::tuple<Us...>>
{
    using type = typename UniqueTuple<std::tuple<Ts...>, AppendIfUnique_t<std::tuple<Us...>, T>>::type;
};

template <typename Tuple>
using UniqueTuple_t = typename UniqueTuple<Tuple>::type;

template <typename... SystemTypes>
constexpr size_t ComponentCount = std::tuple_size<UniqueTuple_t<typename ComponentCollector<SystemTypes...>::type>>::value;