#pragma once

#include <memory>

#include "ArchetypeNode.h"

template <typename... ArchetypeTypes>
class ArchetypeManager 
{
public:
    template <typename... ComponentTypes>
    void addEntity(Entity entity, ComponentTypes&&... components) 
    {
        getArchetype<ComponentTypes...>().addEntity(entity, std::forward<ComponentTypes>(components)...);
    }

    template <typename... ComponentTypes>
    void removeEntity(Entity entity) 
    {
        getArchetype<ComponentTypes...>().removeEntity(entity);
    }

    template<typename ComponentType>
    void addComponent(Entity entity, ComponentType&& component)
    {
    }

    template<typename ComponentType>
    void removeComponent(Entity entity)
    {
    }

    void update()
    {
    }

private:
    template <typename... ComponentTypes>
    ArchetypeNode<ComponentTypes...>& getArchetype()
    {
        size_t index = Identifier<ComponentTypes...>::value;

        if (index >= archetypes.size())
            archetypes.resize(index + 1);

        if (archetypes[index] == nullptr)
            archetypes[index] = new Archetype<ComponentTypes...>();

        return static_cast<Archetype<ComponentTypes...>&>(*archetypes[index]);
    }

private:
    inline static std::vector<std::unique_ptr<BaseArchetypeNode>> archetypes;
};
