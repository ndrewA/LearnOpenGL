#pragma once

#include <memory>

#include "EntityExceptions.h"

class EntityKey
{
public:
	bool operator==(const EntityKey& other) { return id == other.id; }

	bool isRemoved() const { return entity.expired(); }

private:
	EntityKey(std::weak_ptr<Entity> entity)
		: entity(std::move(entity)), id(IDCounter++) { }

	Entity getEntity() const 
	{ 
		if (entity.expired()) 
			throw EntityIsAlreadyDestroyedException();

		return *entity.lock(); 
	}

private:
	std::weak_ptr<Entity> entity;
	size_t id;

private:
	inline static size_t IDCounter = 0;

	friend class ECSManager;
};