#pragma once

#include <type_traits>
#include <tuple>
#include <typeinfo>

template <typename T>
struct FunctionTraits : FunctionTraits<decltype(&std::decay_t<T>::operator())> 
{ 
};

template <typename ClassType, typename ReturnType, typename... Args>
struct FunctionTraits<ReturnType(ClassType::*)(Args...)>
{
    using ArgTypes = std::tuple<Args...>;

    static constexpr size_t arity = sizeof...(Args);

    template <size_t N>
    struct Argument
    {
        static_assert(N < arity, "N out of bounds!");
        using type = typename std::tuple_element<N, std::tuple<Args...>>::type;
    };
};