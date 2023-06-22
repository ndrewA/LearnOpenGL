#pragma once

#include <queue>
#include <memory>

#include "MouseEvent.h"
#include "KeyboardEvent.h"
#include "WindowEvent.h"

class EventQueue
{
public:
    void addEvent(const std::shared_ptr<Event>& event) { eventQueue.push(event); }

    std::shared_ptr<Event> getNewEvent()
    {
        if (eventQueue.empty())
            return std::make_unique<NoneEvent>();
        std::shared_ptr<Event> event = std::move(eventQueue.front());
        eventQueue.pop();
        return event;
    }

    bool isEmpty() const { return eventQueue.empty(); }

private:
    std::queue<std::shared_ptr<Event>> eventQueue;
};