#pragma once

#include "ComponentManager.h"
#include "EntityMetadata.h"
#include "SubscriptionManager.h"
#include "TupleToTemplate.h"

template<typename... SystemTypes>
class ComponentContext
{
    using ComponentManager = TupleToTemplate_t<UnqiueComponentTuple<SystemTypes...>, ComponentManager>;
    static constexpr size_t COMPONENT_COUNT = COMPONENT_COUNT<SystemTypes...>;

public:
    template<typename... EntityComponentTypes>
    void addToEntity(Entity entity, EntityComponentTypes&&... components)
    {
        componentManager.addToEntity(entity, std::forward<EntityComponentTypes>(components)...);
        entityMetadata.addToEntity<EntityComponentTypes...>(entity);
        subscriptionManager.updateSubscriptions(entity, entityMetadata.getSignature(entity));
    }

    template<typename ComponentType>
    void removeFromEntity(Entity entity)
    {
        componentManager.removeFromEntity<ComponentType>(entity);
        entityMetadata.removeFromEntity<ComponentType>(entity);
        subscriptionManager.updateSubscriptions(entity, entityMetadata.getSignature(entity));
    }

    void removeEntity(Entity entity)
    {
        auto& componentIndices = entityMetadata.getIndices(entity);
        componentManager.removeEntity(entity, componentIndices);;
        entityMetadata.removeEntity(entity);
        subscriptionManager.removeEntity(entity);
    }

    template<typename ComponentType>
    ComponentType& getComponent(Entity entity)
    {
        return componentManager.getComponent<ComponentType>(entity);
    }

    template<typename ComponentType>
    bool hasComponent(Entity entity) const
    {
        return componentManager.hasComponent<ComponentType>(entity);
    }

    template<typename SystemType>
    const SparseSet<EntityID>& getSubscribersFor() const
    {
        return subscriptionManager.getSubscribersFor<SystemType>();
    }

private:
    ComponentManager componentManager;
    EntityMetadata<COMPONENT_COUNT> entityMetadata;
    SubscriptionManager<SystemTypes...> subscriptionManager;
};
