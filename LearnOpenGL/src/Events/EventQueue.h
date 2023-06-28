#pragma once

#include <queue>
#include <memory>

#include "MouseEvent.h"
#include "KeyboardEvent.h"
#include "WindowEvent.h"

class EventQueue
{
public:
    using EventPtr = std::unique_ptr<Event>;

    void push(EventPtr event) { eventQueue.push(std::move(event)); }
    
    EventPtr pop()
    {
        if (eventQueue.empty())
            return nullptr;
        EventPtr event = std::move(eventQueue.front());
        eventQueue.pop();
        return event;
    }

    bool isEmpty() const { return eventQueue.empty(); }

private:
    std::queue<EventPtr> eventQueue;
};