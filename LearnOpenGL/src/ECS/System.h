#pragma once

#include "SystemContext.h"

class System
{
public:
	virtual ~System() = default;

	virtual void onAdded() = 0;
	virtual void update(float deltaTime, SystemContext& context) = 0;
	virtual void onRemoved() = 0;

	void enable(bool enabled) { this->enabled = enabled; }
	bool isEnabled() const { return enabled; }
private:
	bool enabled = true;
};