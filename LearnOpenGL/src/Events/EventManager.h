#pragma once

#include "EventBus.h"
#include "EventQueue.h"

class EventManager
{
public:
	template<typename EventType>
	int registerListenerFor(const typename EventListener<EventType>::EventCallBackFn& callBack) 
	{ 
		return eventBus.registerListenerFor<EventType>(callBack);
	}

	void unregisterListener(const int listenerID) 
	{ 
		eventBus.unregisterListener(listenerID);
	}

	void pushEvent(const std::shared_ptr<Event>& event) 
	{ 
		eventQueue.push(event); 
	}

	void publishEvents()
	{
		eventBus.publishEvent(eventQueue);
	}

private:
	EventBus eventBus;
	EventQueue eventQueue;
};