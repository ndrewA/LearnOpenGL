#pragma once

#include <stdexcept>

#include "Entity.h"

class ComponentEntityNotFoundException : public std::runtime_error
{
public:
    ComponentEntityNotFoundException(Entity entity, const std::string& componentType)
        : std::runtime_error(entity + " not found in component pool: " + componentType) { }
};