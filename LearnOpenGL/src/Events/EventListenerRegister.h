#pragma once

#include <vector>
#include <memory>
#include <algorithm>

#include "EventListener.h"

class EventListenerRegister
{
public:
	using ListenerList = std::vector<std::unique_ptr<BaseEventListener>>;

	template<typename EventType>
	int registerListenerFor(const typename EventListener<EventType>::EventCallBackFn& callBack)
	{
		static int listenerID = 0;

		std::unique_ptr<BaseEventListener> listener = std::make_unique<EventListener<EventType>>(callBack, listenerID);
		listeners.push_back(std::move(listener));

		return listenerID++;
	}

	void unregisterListener(const int listenerID)
	{
		listeners.erase(
			std::remove_if(listeners.begin(), listeners.end(), [listenerID](const auto& listener) {
				return listenerID == listener->getID();
				}),
			listeners.end()
		);
	}

	ListenerList::iterator			begin()			{ return listeners.begin(); }
	ListenerList::const_iterator	begin() const	{ return listeners.begin(); }
	ListenerList::iterator			end()			{ return listeners.end();	}
	ListenerList::const_iterator	end() const		{ return listeners.end();	}

private:
	ListenerList listeners;
};