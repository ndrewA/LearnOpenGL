#pragma once

#include <iterator>
#include <algorithm>

#include "ArchetypeStorage.h"

class ArchetypeQuery
{
public:
    using EntitySet = std::unordered_set<Entity>;

    ArchetypeQuery(ArchetypeStorage& archetypeStorage)
        : archetypeStorage(archetypeStorage) { }

    template<typename... ComponentTypes>
    EntitySet findCommonEntities() 
    {
        std::vector<EntitySet> entitySets;
        (entitySets.push_back(archetypeStorage.getEntities<ComponentTypes>()), ...);
        return findCommonEntities(entitySets);
    }

private:
    EntitySet findCommonEntities(const std::vector<EntitySet>& entitySets) const;
    std::vector<EntitySet>::const_iterator findSmallestSet(const std::vector<EntitySet>& entitySets) const;
    EntitySet intersectUnorderedSets(const EntitySet& set1, const EntitySet& set2) const;

private:
    ArchetypeStorage& archetypeStorage;
};