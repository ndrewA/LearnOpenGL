#pragma once

#include <type_traits>

#include "List.h"

namespace ListUtils
{
	template<typename List, typename T>
	struct Contains;

	template <typename T>
	struct Contains<List<>, T>
	{
		static constexpr bool value = false;
	};

	template <typename Head, typename... Tail, typename T>
	struct Contains<List<Head, Tail...>, T>
	{
		static constexpr bool value = std::is_same<Head, T>::value || Contains<List<Tail...>, T>::value;
	};
}

template <typename List1, typename List2>
struct IsSubset;

template <typename... Ts, typename... Us>
struct IsSubset<List<Ts...>, List<Us...>> 
{
	static constexpr bool value = (... && (ListUtils::Contains<List<Us...>, Ts>::value));
};