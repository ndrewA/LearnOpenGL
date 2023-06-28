#pragma once

#include <queue>
#include <memory>

#include "MouseEvent.h"
#include "KeyboardEvent.h"
#include "WindowEvent.h"

class EventQueue
{
public:
    void push(const std::shared_ptr<Event>& event) { eventQueue.push(event); }

    std::shared_ptr<Event> pop()
    {
        if (eventQueue.empty())
            return nullptr;
        std::shared_ptr<Event> event = std::move(eventQueue.front());
        eventQueue.pop();
        return event;
    }

    bool isEmpty() const { return eventQueue.empty(); }

private:
    std::queue<std::shared_ptr<Event>> eventQueue;
};