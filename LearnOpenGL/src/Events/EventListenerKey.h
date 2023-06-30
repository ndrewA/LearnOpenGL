#pragma once

#include "EventListenerID.h"

#include "EventListenerRegister.h"

class EventListenerKey
{
public:
    EventListenerKey(std::shared_ptr<EventListenerID> listenerID)
        : listenerID(std::move(listenerID)) { }

    const EventListenerID& getListenerID() const { return *listenerID; }

private:
    std::shared_ptr<EventListenerID> listenerID;
};
