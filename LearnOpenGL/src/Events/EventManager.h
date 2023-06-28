#pragma once

#include "EventBus.h"
#include "EventQueue.h"

class EventManager
{
public:
	template<typename EventType>
	requires std::derived_from<EventType, Event>
	ListenerID registerListenerFor(const typename EventListener<EventType>::EventCallBackFn& callBack) 
	{ 
		return eventBus.registerListenerFor<EventType>(callBack);
	}

	void unregisterListener(ListenerID& listenerID)
	{ 
		eventBus.unregisterListener(listenerID);
	}

	template<typename EventType, typename... Args>
	requires std::derived_from<EventType, Event>
	void pushEvent(Args&&... args) 
	{ 
		eventQueue.push(std::make_unique<EventType>(std::forward<Args>(args)...)); 
	}

	void publishEvents()
	{
		eventBus.publishEvent(eventQueue);
	}

private:
	EventBus eventBus;
	EventQueue eventQueue;
};