#pragma once

#include <list>
#include <memory>
#include <stdexcept>

#include "System.h"

class SystemManager
{
public:
	template<typename SystemType, typename... Args>
	requires std::derived_from<SystemType, System>
	bool addSystem(Args&&... args)
	{
		if (hasSystem<SystemType>())
			return false;

		std::unique_ptr<System> system = std::make_unique<SystemType>(std::forward<Args>(args)...);
		system->onAdded();
		systems.emplace_back(std::move(system));
		return true;
	}

	template<typename SystemType>
	requires std::derived_from<SystemType, System>
	bool removeSystem()
	{
		const auto it = std::find_if(systems.begin(), systems.end(), [](const auto& system) {
			return dynamic_cast<SystemType*>(system.get()) != nullptr;
		});

		if (it == systems.end())
			return false;

		(*it)->onRemoved();
		systems.erase(it);
		return true;
	}

	template<typename SystemType>
	requires std::derived_from<SystemType, System>
	bool hasSystem() const
	{
		return std::any_of(systems.begin(), systems.end(), [](const auto& system) {
			return dynamic_cast<SystemType*>(system.get()) != nullptr;
		});
	}

	template<typename SystemType>
	requires std::derived_from<SystemType, System>
	SystemType& getSystem() 
	{
		auto it = std::find_if(systems.begin(), systems.end(), [](const auto& system) {
			return dynamic_cast<SystemType*>(system.get()) != nullptr;
		});

		if (it == systems.end()) 
			return nullptr;

		return static_cast<SystemType&>(*it->get());
	}

	void updateSystems(const float deltaTime, EntityManager& entityManager) const 
	{
		for (auto& system : systems)
			if(system->isEnabled())
				system->update(deltaTime, entityManager);
	}

private:
	std::vector<std::unique_ptr<System>> systems;
};