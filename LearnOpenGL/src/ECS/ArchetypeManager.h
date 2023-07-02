#pragma once

#include <memory>
#include <vector>

#include "Archetype.h"
#include "TypeTag.h"

class ArchetypeManager
{
public:
	template<typename ComponentType>
	void addComponent(Entity entity)
	{
		getArchetype<ComponentType>().addEntity(entity);
	}

	template<typename ComponentType>
	void removeComponent(Entity entity)
	{
		getArchetype<ComponentType>().removeEntity(entity);
	}

	void removeEntity(Entity entity)
	{
		for (auto& archetype : archetypes)
			archetype->removeEntity(entity);
	}

	template<typename ComponentType>
	const std::set<Entity>& getEntities() const
	{
		return getArchetype<ComponentType>().getEntities();
	}

private:
	template<typename ComponentType>
	Archetype<ComponentType>& getArchetype()
	{
		size_t index = ComponentTypeTag<ComponentType>::index;

		if (index >= archetypes.size())
			archetypes.resize(index + 1);

		if (archetypes[index] == nullptr)
			archetypes[index] = std::make_unique<Archetype<ComponentType>>();

		return static_cast<Archetype<ComponentType>&>(*archetypes[index]);
	}

private:
	std::vector<std::unique_ptr<BaseArchetype>> archetypes;
};