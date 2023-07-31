#pragma once

#include "SparseSet.h"

template<typename SystemType>
class EntitySubscription
{
public:
    void subscribe(Entity entity)
    {
        subscribers.insert(entity.id);
    }

    void unsubscribe(Entity entity)
    {
        subscribers.remove(entity.id);
    }

    const SparseSet<EntityID>& getSubscribers() const
    {
        return subscribers;
    }

private:
    SparseSet<EntityID> subscribers;
};