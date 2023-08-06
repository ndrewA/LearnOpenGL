#pragma once

#include <iostream>

#include "NewECS/TopologicallySortTuple.h"

template <typename T>
constexpr auto type_name() noexcept {
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
    suffix = ">(void) noexcept";
#else
    static_assert(false, "Unsupported compiler!");
#endif
    name.remove_prefix(prefix.size());
    name.remove_suffix(suffix.size());
    return name;
}

template <typename T>
void print()
{
    std::cout << type_name<T>() << '\n';
}

struct System1 {};
struct System2 {};
struct System3 {};
struct System4 {};
struct System5 {};
struct System6 {};
struct System7 {};
struct System8 {};
struct System9 {};
struct System10 {};
struct System11 {};
struct System12 {};
struct System13 {};
struct System14 {};
struct System15 {};
struct System16 {};
struct System17 {};
struct System18 {};
struct System19 {};
struct System20 {};

using SystemNode1 = SystemNode<System1, std::tuple<>>;
using SystemNode2 = SystemNode<System2, std::tuple<System1>>;
using SystemNode3 = SystemNode<System3, std::tuple<System1, System2>>;
using SystemNode4 = SystemNode<System4, std::tuple<System2>>;
using SystemNode5 = SystemNode<System5, std::tuple<System3, System4>>;
using SystemNode6 = SystemNode<System6, std::tuple<System5>>;
using SystemNode7 = SystemNode<System7, std::tuple<System6>>;
using SystemNode8 = SystemNode<System8, std::tuple<System7, System2>>;
using SystemNode9 = SystemNode<System9, std::tuple<System8, System3>>;
using SystemNode10 = SystemNode<System10, std::tuple<System9>>;
using SystemNode11 = SystemNode<System11, std::tuple<System10, System4>>;
using SystemNode12 = SystemNode<System12, std::tuple<System11, System5>>;
using SystemNode13 = SystemNode<System13, std::tuple<>>;
using SystemNode14 = SystemNode<System14, std::tuple<System13, System7>>;
using SystemNode15 = SystemNode<System15, std::tuple<System14, System8>>;
using SystemNode16 = SystemNode<System16, std::tuple<System15, System9>>;
using SystemNode17 = SystemNode<System17, std::tuple<System16, System10>>;
using SystemNode18 = SystemNode<System18, std::tuple<System17, System11>>;
using SystemNode19 = SystemNode<System19, std::tuple<System18, System12>>;
using SystemNode20 = SystemNode<System20, std::tuple<System19, System13>>;

int main()
{
    
    using SystemNodes = std::tuple<
        SystemNode1, SystemNode2, SystemNode3, SystemNode4, SystemNode5,
        SystemNode16, SystemNode17, SystemNode18, SystemNode19, SystemNode20,
        SystemNode11, SystemNode12, SystemNode13, SystemNode14, SystemNode15,
        SystemNode6, SystemNode7, SystemNode8, SystemNode9, SystemNode10
    >;
    using SortedSystemNodes = TopologicallySort_t<SystemNodes>;
    print<SortedSystemNodes>();

    return 0;
}
