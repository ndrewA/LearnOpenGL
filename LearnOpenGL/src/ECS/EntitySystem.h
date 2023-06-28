#pragma once

#include "EntityManager.h"

class EntitySystem
{
public:
	virtual ~EntitySystem() = default;

	virtual void onAdded() = 0;
	virtual void update(const float deltaTime, EntityManager& entityManager) = 0;
	virtual void onRemoved() = 0;
};