#pragma once

#include <string_view>

template <typename T>
constexpr auto typeName()
{
    std::string_view name, prefix, suffix;
    name = "Error: unsupported compiler";
#ifdef __clang__
    name = __PRETTY_FUNCTION__;
    prefix = "auto typeName() [T = ";
    suffix = "]";
#elif defined(__GNUC__)
    name = __PRETTY_FUNCTION__;
    prefix = "constexpr auto typeName() [with T = ";
    suffix = "]";
#elif defined(_MSC_VER)
    name = __FUNCSIG__;
    prefix = "auto __cdecl typeName<";
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