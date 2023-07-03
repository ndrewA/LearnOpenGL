#pragma once

#include <unordered_set>

#include "Entity.h"

namespace std
{
    template<>
    struct hash<Entity>
    {
        std::size_t operator()(const Entity& entity) const { return std::hash<size_t>{}(entity.index); }
    };
}

inline bool operator==(const Entity& lhs, const Entity& rhs) { return lhs.index == rhs.index; }

class BaseArchetype
{
public:
	virtual void addEntity(Entity entity) = 0;
	virtual void removeEntity(Entity entity) = 0;

	virtual const std::unordered_set<Entity>& getEntities() const = 0;
};

template<typename ComponentType>
class Archetype : public BaseArchetype
{
public:
	void addEntity(Entity entity) override { entities.insert(entity); }
	void removeEntity(Entity entity) override { entities.erase(entity); }

	const std::unordered_set<Entity>& getEntities() const override { return entities; }

private:
	std::unordered_set<Entity> entities;
};