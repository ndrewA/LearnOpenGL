#pragma once

#include <set>

#include "Entity.h"

class BaseArchetype
{
public:
	virtual void addEntity(Entity entity) = 0;
	virtual void removeEntity(Entity entity) = 0;

	virtual const std::set<Entity>& getEntities() const = 0;
};

template<typename ComponentType>
class Archetype : public BaseArchetype
{
public:
	void addEntity(Entity entity) override { entities.insert(entity); }
	void removeEntity(Entity entity) override { entities.erase(entity); }

	const std::set<Entity>& getEntities() const override { return entities; }

private:
	std::set<Entity> entities;
};