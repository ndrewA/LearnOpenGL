#pragma once

#include <stdexcept>
#include <string>

#include "Entity.h"

class EntityOutOfBoundsException : std::runtime_error
{
public:
	EntityOutOfBoundsException(Entity entity)
		: runtime_error("Entity: " + std::to_string(entity.index) + " is out of bounds!") { }
};

class EntityIsAlreadyDestroyedException : std::runtime_error
{
public:
	EntityIsAlreadyDestroyedException()
		: runtime_error("Attempted to access a destroyed entity") { }
};