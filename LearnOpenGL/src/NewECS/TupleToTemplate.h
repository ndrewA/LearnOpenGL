#pragma once

#include <tuple>

template <typename Tuple, template <typename...> class T>
struct TupleToTemplate;

template <typename... Ts, template <typename...> class T>
struct TupleToTemplate<std::tuple<Ts...>, T> {
    using type = T<Ts...>;
};

template <typename Tuple, template <typename...> class T>
using TupleToTemplate_t = typename TupleToTemplate<Tuple, T>::type;
