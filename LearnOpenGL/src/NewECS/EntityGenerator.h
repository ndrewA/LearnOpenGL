#pragma once

#include <queue>

#include "SparseSet.h"

class EntityGenerator
{
public:
	Entity generateEntity();
	void freeEntity(Entity entity);

private:
	Entity generateNewEntity();
	Entity reuseEntity();

private:
	SparseSet<EntityID> entities;
	std::queue<EntityID> freeIDs;
};
