#pragma once

#include <memory>

#include "EventListenerRegister.h"

class EventBus
{
public:
	template<typename EventType>
	int registerListener(const typename EventListener<EventType>::EventCallBackFn& callBack)
	{
		const int listenerID = generateUniqueID();
		std::unique_ptr<BaseEventListener> listener = std::make_unique<EventListener<EventType>>(callBack, listenerID);

		listeners.registerListener(std::move(listener));

		return listenerID;
	}

	void unregisterListener(const int listenerID)
	{
		listeners.unregisterListener(listenerID);
	}

	void publishEvent(const std::shared_ptr<Event>& event) const
	{
		for (const auto& listener : listeners) {
			if (listener->isEventType(event))
				listener->dispatchEvent(event);

			if (event->isHandeled())
				break;
		}
	}

private:
	int generateUniqueID() {
		static int currentID = 0;
		return currentID++;
	}

private:
	EventListenerRegister listeners;
};