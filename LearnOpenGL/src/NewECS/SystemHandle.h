#pragma once

#include <tuple>

template<typename TSystem, typename... TDependencies>
class SystemHandle
{
public:
	using SystemType = TSystem;
	using Dependencies = std::tuple<TDependencies...>;
};