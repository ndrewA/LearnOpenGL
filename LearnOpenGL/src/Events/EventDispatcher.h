#pragma once

#include <memory>
#include <vector>
#include <type_traits>

#include "KeyboardEvent.h"
#include "MouseEvent.h"
#include "WindowEvent.h"
#include "Command.h"

class EventDispatcher
{
public:
	template<typename EventType>
	void registerEventListener(std::shared_ptr<Command> command)
	{
		std::unique_ptr<ListenerBase> listener = std::make_unique<Listener<EventType>>(std::move(command));
		listeners.emplace_back(std::move(listener));
	}

	void dispatchEvent(const Event& event)
	{
		for (auto& listener : listeners)
			if (listener->isEventType(event))
				listener->dispatchEvent(event);
	}

private:
	class ListenerBase
	{
	public:
		virtual ~ListenerBase() = default;
		virtual void dispatchEvent(const Event&) = 0;
		virtual bool isEventType(const Event& event) = 0;
	};

	template<typename EventType>
	class Listener : public ListenerBase
	{
	public:
		explicit Listener(const std::shared_ptr<Command>& command) : command(command) { }
		void dispatchEvent(const Event&) override { command->execute(); } 

		bool isEventType(const Event& event) override { return EventType::getStaticType() == event.getType(); }
	private:
		std::shared_ptr<Command> command;
	};

private:

private:
	std::vector<std::unique_ptr<ListenerBase>> listeners;
};

