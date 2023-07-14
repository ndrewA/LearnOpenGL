#pragma once

#include <memory>

#include "TupleUtils.h"
#include "EmptyArchetype.h"
#include "TupleSort.h"
#include "TupleInsert.h"

class ArchetypeGraph
{
public:
    template <typename... CurrentComponentTypes, typename NewComponentType>
    auto addComponent(Entity<CurrentComponentTypes...> currentEntity, NewComponentType newComponent)
    {
        auto& currentArchetype = getArchetype<CurrentComponentTypes...>();
        auto currentComponents = currentArchetype.removeEntityAndGetComponents(currentEntity);
        auto newComponents = binarySearchInsert(currentComponents, newComponent);

        using SortedTuple = QuickSort_t<CurrentComponentTypes..., NewComponentType>;
        using NewEntityType = InstantiateWithTuple<SortedTuple, Entity>::type;
        NewEntityType newEntity{ currentEntity.ID };

        auto& newArchetype = getArchetype<CurrentComponentTypes..., NewComponentType>();

        newArchetype.addEntity(newEntity, newComponents);

        return newEntity;
    }

private:
    template <typename... ComponentTypes>
    auto& getArchetype()
    {
        using SortedTuple = QuickSort_t<ComponentTypes...>;
        size_t index = TupleIdentifier<SortedTuple>::value;

        if (index >= archetypes.size())
            archetypes.resize(2 * index + 1);

        if (archetypes[index] == nullptr) {
            using SortedArchetype = typename InstantiateWithTuple<SortedTuple, Archetype>::type;
            archetypes[index] = std::make_unique<SortedArchetype>();
        }
        return static_cast<typename InstantiateWithTuple<SortedTuple, Archetype>::type&>(*archetypes[index]);
    }

private:
    inline static std::vector<std::unique_ptr<BaseArchetype>> archetypes;
};