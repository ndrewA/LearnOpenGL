#pragma once

#include <vector>
#include <memory>

#include <algorithm>

#include "EventListener.hpp"

#include <iostream>

class EventListenerRegister
{
public:
	void registerListener(std::unique_ptr<BaseEventListener> listener) { listeners.emplace_back(std::move(listener)); }
	void unregisterListener(const int listenerID)
	{
		auto it = std::remove_if(listeners.begin(), listeners.end(), [listenerID](const auto& listener) {
			return listenerID == listener->getID();
			});
		listeners.erase(it);
	}

	std::vector<std::unique_ptr<BaseEventListener>>::iterator begin() { return listeners.begin(); }
	std::vector<std::unique_ptr<BaseEventListener>>::iterator end() { return listeners.end(); }
	std::vector<std::unique_ptr<BaseEventListener>>::const_iterator begin() const { return listeners.begin(); }
	std::vector<std::unique_ptr<BaseEventListener>>::const_iterator end() const { return listeners.end(); }

private:
	std::vector<std::unique_ptr<BaseEventListener>> listeners;
};