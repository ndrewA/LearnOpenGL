#pragma once

#include <memory>

#include "EmptyArchetype.h"
#include "TupleSort.h"
#include "TupleInsert.h"
#include "TupleRemove.h"
#include "TupleUtils.h"

class ArchetypeGraph
{
public:
    template <typename... CurrentComponentTypes, typename NewComponentType>
    requires (Contains<NewComponentType, CurrentComponentTypes...>::value == false)
    [[nodiscard("Entity type will change, you will need it!")]] 
    auto addComponent(Entity<CurrentComponentTypes...> currentEntity, NewComponentType newComponent)
    {
        auto currentComponents = removeEntityFromCurrentArchetype<CurrentComponentTypes...>(currentEntity);
        auto newComponents = insertNewComponent(currentComponents, newComponent);

        using SortedTuple = QuickSort_t<CurrentComponentTypes..., NewComponentType>;
        using NewEntityType = typename InstantiateWithTuple<SortedTuple, Entity>::type;
        NewEntityType newEntity{ currentEntity.ID };

        return addEntityToNewArchetype<SortedTuple>(newEntity, newComponents);
    }

    template <typename RemovedComponentType, typename... CurrentComponentTypes>
    requires (Contains<RemovedComponentType, CurrentComponentTypes...>::value == true)
    [[nodiscard("Entity type will change, you will need it!")]]
    auto removeComponent(Entity<CurrentComponentTypes...> currentEntity)
    {
        auto currentComponents = removeEntityFromCurrentArchetype<CurrentComponentTypes...>(currentEntity);
        auto newComponents = removeComponentFromComponents<RemovedComponentType>(currentComponents);

        using RemovedTuple = RemoveType_t<RemovedComponentType, CurrentComponentTypes...>;
        using NewEntityType = typename InstantiateWithTuple<RemovedTuple, Entity>::type;
        NewEntityType newEntity{ currentEntity.ID };

        return addEntityToNewArchetype<RemovedTuple>(newEntity, newComponents);
    }

private:
    template <typename... CurrentComponentTypes>
    auto removeEntityFromCurrentArchetype(Entity<CurrentComponentTypes...> currentEntity)
    {
        auto& currentArchetype = getArchetype<CurrentComponentTypes...>();
        return currentArchetype.removeEntityAndGetComponents(currentEntity);
    }

    template <typename... CurrentComponentTypes, typename NewComponentType>
    auto insertNewComponent(std::tuple<CurrentComponentTypes...> currentComponents, NewComponentType newComponent)
    {
        return binarySearchInsert(currentComponents, newComponent);
    }

    template <typename SortedTuple, typename NewEntityType, typename ComponentsTuple>
    auto addEntityToNewArchetype(NewEntityType newEntity, ComponentsTuple newComponents)
    {
        auto& newArchetype = getArchetype<SortedTuple>();
        newArchetype.addEntity(newEntity, newComponents);
        return newEntity;
    }

    template <typename RemovedComponentType, typename... ComponentTypes>
    auto removeComponentFromComponents(std::tuple<ComponentTypes...> components)
    {
        return removeTypeFromTuple<RemovedComponentType>(components);
    }

private:
    template <typename... ComponentTypes>
    auto& getArchetype()
    {
        using SortedTuple = QuickSort_t<ComponentTypes...>;
        size_t index = Identifier<SortedTuple>::value;

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
