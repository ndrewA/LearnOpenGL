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
	ListenerID registerListenerFor(const typename EventListener<EventType>::EventCallBackFn& callBack)
	{
		static int currentID = 0;
		ListenerID listenerID(currentID);
		++currentID;

		std::unique_ptr<BaseEventListener> listener = std::make_unique<EventListener<EventType>>(callBack, listenerID);
		listeners.push_back(std::move(listener));

		return listenerID;
	}

	void unregisterListener(ListenerID& listenerID)
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
};
