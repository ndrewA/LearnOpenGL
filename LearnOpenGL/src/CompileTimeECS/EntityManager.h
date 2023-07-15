#pragma once

#include <vector>

#include "Entity.h"

class EntityManager
{
public:
	template<typename... ComponentTypes>
	Entity<ComponentTypes...> createEntity()
	{
		
	}

	template<typename... ComponentTypes>
	void freeEntity(Entity<ComponentTypes...> entity)
	{
		freeEntity.push_back(entity.ID);
	}

private:



private:
	inline static size_t maxEntityCount = 0;
	inline static std::vector<size_t> freeEntityIDs;
};