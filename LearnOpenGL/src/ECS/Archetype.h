#pragma once

#include <vector>

#include "Entity.h"
#include "SparseSet.h"

class Archetype
{
public:
    void addEntity(Entity entity) { entities.push_back(entity); }

    void removeEntity(Entity entity) 
    { 
        entities.erase(
            std::remove_if(
                entities.begin(),
                entities.end(),
                [entity](Entity e) { return e.index == entity.index; }  
            ),
            entities.end()
        );
    }

    bool hasEntity(Entity entity) const 
    { 
        return std::find_if(
            entities.begin(),
            entities.end(),
            [entity](const Entity& e) { return e.index == entity.index; }  
        ) != entities.end();
    }

    const std::vector<Entity>& getEntities() const { return entities; }

private:
    std::vector<Entity> entities;
};
