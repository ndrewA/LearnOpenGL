#pragma once

#include <tuple>

template <typename... ComponentTypes>
struct Entity
{
	using Signature = std::tuple<ComponentTypes...>;
	size_t ID;
};

template <typename... ComponentTypes>
bool operator==(const Entity<ComponentTypes...>& thisEntity, const Entity<ComponentTypes...>& otherEntity)
{
	return thisEntity.ID == otherEntity.ID;
}