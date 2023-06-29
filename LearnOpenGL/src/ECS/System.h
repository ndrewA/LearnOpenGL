#pragma once

#include "EntityManager.h"

class System
{
public:
	virtual ~System() = default;

	virtual void onAdded() = 0;
	virtual void update(const float deltaTime, EntityManager& entityManager) = 0;
	virtual void onRemoved() = 0;

	void enable(const bool enabled) { this->enabled = enabled; }
	bool isEnabled() const { return enabled; }

private:
	bool enabled = true;
};