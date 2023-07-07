#pragma once

#include <list>
#include <memory>
#include <stdexcept>

#include "System.h"
#include "SystemExceptions.h"
#include "TypeTag.h"

class SystemManager
{
public:
	SystemManager(const SystemContext& context)
		: context(context) { }

	template<typename SystemType, typename... Args>
	void addSystem(Args&&... args)
	{
		size_t index = SystemTypeTag<SystemType>::index;
		
		if(index >= systems.size())
			systems.resize(index + 1);

		if(systems[index])
			throw SystemAlreadyAddedException(typeid(SystemType).name());

		systems[index] = std::make_unique<SystemType>(std::forward<Args>(args)...);
		systems[index]->onAdded();
	}

	template<typename SystemType>
	void removeSystem()
	{
		size_t index = SystemTypeTag<SystemType>::index;

		if(index >= systems.size() || systems[index] == nullptr)
			throw SystemNotFoundException(typeid(SystemType).name());

		systems[index]->onRemoved();
		systems[index].reset();
	}

	template<typename SystemType>
	bool hasSystem() const
	{
		size_t index = SystemTypeTag<SystemType>::index;

		return index < systems.size() && systems[index];
	}

	template<typename SystemType>
	void enableSystem(bool enabled)
	{
		size_t index = SystemTypeTag<SystemType>::index;
		
		systems[index]->enabled(enabled);
	}

	void updateSystems(float deltaTime) 
	{
		for (auto& system : systems)
			if(system != nullptr && system->isEnabled())
				system->update(deltaTime, context);
	}

private:
	inline static std::vector<std::unique_ptr<System>> systems;

	SystemContext context;
};