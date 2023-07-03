#include "ArchetypeQuery.h"

ArchetypeQuery::EntitySet ArchetypeQuery::findCommonEntities(const std::vector<EntitySet>& entitySets) const
{
    if (entitySets.empty())
        return { };

    auto smallestSetIt = findSmallestSet(entitySets);
    EntitySet commonEntities = *smallestSetIt;

    for (auto it = entitySets.begin(); it != entitySets.end(); ++it) {
        if (it == smallestSetIt)
            continue;

        commonEntities = intersectUnorderedSets(commonEntities, *it);
    }

    return commonEntities;
}

std::vector<ArchetypeQuery::EntitySet>::const_iterator ArchetypeQuery::
    findSmallestSet(const std::vector<EntitySet>& entitySets) const
{
    return std::min_element(entitySets.begin(), entitySets.end(),
        [](const EntitySet& a, const EntitySet& b) {
            return a.size() < b.size();
        });
}

ArchetypeQuery::EntitySet ArchetypeQuery::
    intersectUnorderedSets(const EntitySet& set1, const EntitySet& set2) const
{
    EntitySet intersection;
    for (const auto& entity : set1)
        intersection.insert(entity);
    return intersection;
}