#pragma once

#include <memory>

#include "EventListenerRegister.h"
#include "EventQueue.h"

class EventBus
{
public:
	template<typename EventType>
	ListenerID registerListenerFor(const typename EventListener<EventType>::EventCallBackFn& callBack)
	{
		return listeners.registerListenerFor<EventType>(callBack);
	}

	void unregisterListener(ListenerID& listenerID)
	{
		listeners.unregisterListener(listenerID);
	}

	void publishEvent(EventQueue& eventQueue) const
	{
		while(const auto& event = eventQueue.pop()) {
			for (const auto& listener : listeners) {
				if (listener->isEventType(*event.get()))
					listener->dispatchEvent(*event.get());

				if (event->isHandeled())
					break;
			}
		}
	}

private:
	EventListenerRegister listeners;
};