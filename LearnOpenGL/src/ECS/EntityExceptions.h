#pragma once

#include <stdexcept>
#include <string>

#include "Entity.h"

class EntityOutOfBoundsException : std::runtime_error
{
public:
	EntityOutOfBoundsException(const Entity entity)
		: runtime_error("Entity: " + std::to_string(entity) + " is out of bounds!") { }
};