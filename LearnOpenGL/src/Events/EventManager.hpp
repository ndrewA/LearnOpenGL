#pragma once

#include "EventBus.hpp"
#include "EventListenerRegister.h"
#include "EventQueue.h"

class EventManager
{
public:
	template<typename EventType>
	int registerListener(const typename EventListener<EventType>::EventCallBackFn& callBack) { return eventBus.registerListener<EventType>(callBack); }
	void unregisterListener(const int listenerID) { eventBus.unregisterListener(listenerID); }

	void addEvent(const std::shared_ptr<Event>& event) { events.addEvent(event); }
	void publishEventsToBus() 
	{  
		while (!events.isEmpty())
			eventBus.publishEvent(events.getNewEvent());
	}

private:
	EventBus eventBus;
	EventQueue events;
};
