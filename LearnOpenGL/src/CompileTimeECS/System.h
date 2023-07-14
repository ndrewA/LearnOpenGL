#pragma once

#include "Entity.h"

template <typename... ComponentTypes>
class System 
{
public:
    virtual void update(Entity entity, ComponentTypes&... components) = 0;
};