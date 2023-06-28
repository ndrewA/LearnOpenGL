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
		if (listenerID.isRegisterd() == false)
			throw std::runtime_error("Listener already unregistered!");

		listeners.erase(
			std::remove_if(listeners.begin(), listeners.end(), [&listenerID](const auto& listener) {
					if (listenerID.get() != listener->getID().get())
						return false;
					listenerID.unregister();
					return true;
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
