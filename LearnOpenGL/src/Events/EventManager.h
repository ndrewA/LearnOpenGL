#pragma once

#include "EventBus.h"
#include "EventQueue.h"

class EventManager
{
public:
	template<typename EventType>
	requires std::derived_from<EventType, Event>
	[[nodiscard]] EventListenerKey registerListenerFor(const typename EventListener<EventType>::EventCallBackFn& callBack)
	{ 
		return eventBus.registerListenerFor<EventType>(callBack);
	}

	template<typename EventType>
	requires std::derived_from<EventType, Event>
	void registerPermanentListenerFor(const typename EventListener<EventType>::EventCallBackFn& callBack)
	{
		eventBus.registerPermanentListenerFor<EventType>(callBack);
	}

	void unregisterListener(const EventListenerKey& listenerKey)
	{ 
		eventBus.unregisterListener(listenerKey);
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