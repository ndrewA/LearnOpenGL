#pragma once

#include <queue>

#include "SparseSet.h"

class EntityGenerator
{
public:
	Entity generateEntity();
	void freeEntity(Entity entity);

	const std::vector<Entity>& getEntities() const { return entities.getEntities(); }

private:
	Entity generateNewEntity();
	Entity reuseEntity();

private:
	SparseSet entities;
	std::queue<EntityID> freeIDs;
};
