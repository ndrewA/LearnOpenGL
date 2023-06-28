#pragma once

#include <vector>
#include <memory>
#include <stdexcept>

#include "EntitySystem.h"

class SystemManager
{
public:
	template<typename SystemType, typename... Args>
	requires std::derived_from<SystemType, System>
	void addSystem(Args&&... args)
	{
		const auto system = std::make_shared<SystemType>(std::forward<Args>(args)...);
		systems.emplace_back(system);
		system->onAdded();
	}

	template<typename SystemType>
	requires std::derived_from<SystemType, System>
	void removeSystem()
	{
		const auto it = std::find_if(systems.begin(), systems.end(), [](const auto& system) {
			return typeid(*system) == typeid(SystemType);
		});

		if (it == systems.end())
			throw std::runtime_error("System doesn't exist!");

		(*it)->onRemoved();
		systems.erase(it);
	}

	void updateSystems(const float deltaTime, EntityManager& entityManager)
	{
		for (auto& system : systems)
			system->update(deltaTime, entityManager);
	}

private:
	std::vector<std::shared_ptr<System>> systems;
};