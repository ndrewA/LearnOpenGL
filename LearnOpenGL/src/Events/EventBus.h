#pragma once

#include <memory>

#include "EventListenerRegister.h"
#include "EventQueue.h"

#include "EventListenerKey.h"

class EventBus
{
public:
	template<typename EventType>
	EventListenerKey registerListenerFor(const typename EventListener<EventType>::EventCallBackFn& callBack)
	{
		return { listeners.registerListenerFor<EventType>(callBack) };
	}

	void unregisterListener(const EventListenerKey& listenerKey)
	{
		listeners.unregisterListener(listenerKey.getListenerID());
	}

	void publishEvent(EventQueue& eventQueue) const
	{
		while (auto event = eventQueue.pop()) 
			for (const auto& listener : listeners) 
				if (listener->isEventType(*event)) 
					if (listener->dispatchEvent(*event))
						break;

	}

private:
	EventListenerRegister listeners;
};