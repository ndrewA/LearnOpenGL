#pragma once

#include <list>
#include <memory>
#include <stdexcept>
#include <unordered_map>

#include "System.h"
#include "SystemExceptions.h"

class SystemManager
{
public:
	template<typename SystemType, typename... Args>
	void addSystem(Args&&... args)
	{
		const auto typeIndex = std::type_index(typeid(SystemType));
		if (systemLookup.find(typeIndex) != systemLookup.end())
			throw SystemAlreadyAddedException(typeid(SystemType).name());

		std::unique_ptr<System> system = std::make_unique<SystemType>(std::forward<Args>(args)...);

		system->onAdded();
		systems.emplace_back(std::move(system));
		systemLookup[typeIndex] = systems.size() - 1;
	}

	template<typename SystemType>
	void removeSystem()
	{
		const auto typeIndex = std::type_index(typeid(SystemType));
		const auto it = systemLookup.find(typeIndex);

		if (it == systemLookup.end())
			throw SystemNotFoundException(typeid(SystemType).name());

		systems[it->second]->onRemoved();
		systems.erase(systems.begin() + it->second);
		systemLookup.erase(it);
	}

	template<typename SystemType>
	bool hasSystem() const
	{
		const auto typeIndex = std::type_index(typeid(SystemType));
		return systemLookup.find(typeIndex) != systemLookup.end();
	}

	template<typename SystemType>
	void enableSystem(const bool enabled)
	{
		auto system = getSystem<SystemType>();
		
		system->enabled(enabled);
	}

	void updateSystems(const float deltaTime, SystemContext& context) const 
	{
		for (auto& system : systems)
			if(system->isEnabled())
				system->update(deltaTime, context);
	}

private:
	std::vector<std::unique_ptr<System>> systems;
	std::unordered_map<std::type_index, size_t> systemLookup;
};