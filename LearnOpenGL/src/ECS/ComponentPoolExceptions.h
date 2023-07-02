#pragma once

#include <stdexcept>
#include <string>

#include "Entity.h"

class ComponentOutOfBoundsException : public std::runtime_error
{
public:
    ComponentOutOfBoundsException(Entity entity)
        : std::runtime_error(std::to_string(entity.index) + " is out of bounds!") { }
};