#pragma once

#include "EntitySubscription.h"
#include "SystemMetadata.h"
#include "ComponentCount.h"

template<typename... SystemTypes>
class SubscriptionManager
{
    static constexpr size_t COMPONENT_COUNT = COMPONENT_COUNT<SystemTypes...>;
    using EntitySignature = EntitySignature<COMPONENT_COUNT>;

public:
    void updateSubscriptions(Entity entity, const EntitySignature& entitySignature)
    {
        (updateSubscription<SystemTypes>(entity, entitySignature), ...);
    }

    template <typename SystemType>
    const SparseSet<EntityID>& getSubscribersFor() const
    {
        return std::get<EntitySubscription<SystemType>>(entitySubscriptions).getSubscribers();
    }

    void removeEntity(Entity entity)
    {
        (removeFromSubscription<SystemTypes>(entity), ...);
    }

private:
    template <typename SystemType>
    void updateSubscription(Entity entity, const EntitySignature& entitySignature)
    {
        auto& subscription = std::get<EntitySubscription<SystemType>>(entitySubscriptions);

        systemMetadata.matches<SystemType>(entitySignature) ?
            subscription.subscribe(entity)
            : subscription.unsubscribe(entity);
    }

    template <typename SystemType>
    void removeFromSubscription(Entity entity)
    {
        auto& subscription = std::get<EntitySubscription<SystemType>>(entitySubscriptions);
        subscription.unsubscribe(entity);
    }

private:
    std::tuple<EntitySubscription<SystemTypes>...> entitySubscriptions;
    SystemMetadata<SystemTypes...> systemMetadata;
};
