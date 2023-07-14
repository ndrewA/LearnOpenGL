#pragma once

#include <tuple>
#include <type_traits>

template <typename... Ts>
struct Concat;

template <typename... Ts, typename... Us>
struct Concat<std::tuple<Ts...>, std::tuple<Us...>>
{
    using type = std::tuple<Ts..., Us...>;
};

template <typename... Ts>
struct Append;

template <typename... Ts, typename T>
struct Append<std::tuple<Ts...>, T>
{
    using type = std::tuple<Ts..., T>;
};

template <typename T, typename Tuple>
struct Contains;

template <typename T, typename... Ts>
struct Contains<T, std::tuple<Ts...>> {
    static const bool value = std::disjunction_v<std::is_same<T, Ts>...>;
};

template <typename Tuple, template <typename...> class Template>
struct InstantiateWithTuple;

template <typename... Ts, template <typename...> class Template>
struct InstantiateWithTuple<std::tuple<Ts...>, Template>
{
    using type = Template<Ts...>;
};