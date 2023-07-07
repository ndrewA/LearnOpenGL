#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <stdexcept>

#include "EventListener.h"
							
class EventListenerRegister
{
public:
	using ListenerList = std::vector<std::unique_ptr<BaseEventListener>>;

	template<typename EventType>
	std::shared_ptr<EventListenerID> registerListenerFor(const typename EventListener<EventType>::EventCallBackFn& callBack)
	{
		std::shared_ptr<EventListenerID> listenerID(new EventListenerID(currentID++), 
			[this](EventListenerID* listenerID) {
				this->unregisterListener(*listenerID);
				delete listenerID;
			}
		);

		std::unique_ptr<BaseEventListener> listener = std::make_unique<EventListener<EventType>>(callBack, *listenerID);
		listeners.push_back(std::move(listener));

		return listenerID;
	}

	template<typename EventType>
	void registerPermanentListenerFor(const typename EventListener<EventType>::EventCallBackFn& callBack)
	{
		EventListenerID listenerID(currentID++);
		std::unique_ptr<BaseEventListener> listener = std::make_unique<EventListener<EventType>>(callBack, listenerID);
		listeners.push_back(std::move(listener));
	}

	void unregisterListener(const EventListenerID& listenerID)
	{
		listeners.erase(
			std::remove_if(listeners.begin(), listeners.end(), [&listenerID](const auto& listener) {
				return listenerID.get() == listener->getID().get();
				}),
			listeners.end()
		);
	}

	auto begin()		{ return listeners.begin(); }
	auto begin() const	{ return listeners.begin(); }
	auto end()			{ return listeners.end();	}
	auto end()	 const	{ return listeners.end();	}

private:
	ListenerList listeners;
	size_t currentID = 0;
};
	