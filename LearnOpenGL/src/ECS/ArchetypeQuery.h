#pragma once

#include <iterator>
#include <algorithm>

#include "ArchetypeManager.h"

class ArchetypeQuery
{
public:
	ArchetypeQuery(const ArchetypeManager& archetypeManager)
		: archetypeManager(archetypeManager) { }

	template<typename... ComponentTypes>
	std::set<Entity> findCommonEntities() const
	{
		std::vector<std::set<Entity>> entitySets;
		(entitySets.push_back(getArchetype<ComponentTypes>().getEntities()), ...);
		return findCommonEntities(entitySets);
	}

	std::set<Entity> findCommonEntities(const std::vector<std::set<Entity>>& entitySets)
	{
		if (entitySets.empty())
			return { };

		auto smallestSetIt = findSmallestSet(entitySets);
		std::set<Entity> commonEntities = *smallestSetIt;

		for (auto it = entitySets.begin(); it != entitySets.end(); ++it) {
			if (it == smallestSetIt)
				continue;

			commonEntities = intersectSets(commonEntities, *it);
		}

		return commonEntities;
	}

private:
	std::vector<std::set<Entity>>::const_iterator findSmallestSet(const std::vector<std::set<Entity>>& entitySets)
	{
		return std::min_element(entitySets.begin(), entitySets.end(),
			[](const std::set<Entity>& a, const std::set<Entity>& b) {
				return a.size() < b.size();
			});
	}

	std::set<Entity> intersectSets(const std::set<Entity>& set1, const std::set<Entity>& set2)
	{
		std::set<Entity> intersection;
		std::set_intersection(set1.begin(), set1.end(),
			set2.begin(), set2.end(),
			std::inserter(intersection, intersection.begin()));
		return intersection;
	}

private:
	const ArchetypeManager& archetypeManager;
};