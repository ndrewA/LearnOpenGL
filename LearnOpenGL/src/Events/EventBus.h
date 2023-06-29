#pragma once

#include <memory>

#include "EventListenerRegister.h"
#include "EventQueue.h"

class EventBus
{
public:
	template<typename EventType>
	EventListenerID registerListenerFor(const typename EventListener<EventType>::EventCallBackFn& callBack)
	{
		return listeners.registerListenerFor<EventType>(callBack);
	}

	void unregisterListener(EventListenerID& listenerID)
	{
		listeners.unregisterListener(listenerID);
	}

	void publishEvent(EventQueue& eventQueue) const
	{
		while(const auto& event = eventQueue.pop()) {
			for (const auto& listener : listeners) {
				if (listener->isEventType(*event.get()))
					listener->dispatchEvent(*event.get());

				if (event->isHandled())
					break;
			}
		}
	}

private:
	EventListenerRegister listeners;
};