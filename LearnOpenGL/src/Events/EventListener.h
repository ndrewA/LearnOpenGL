#pragma once

#include <functional>

#include "MouseEvent.h"
#include "KeyboardEvent.h"
#include "WindowEvent.h"

class BaseEventListener
{
public:
	virtual ~BaseEventListener() = default;
	virtual const void dispatchEvent(const std::shared_ptr<Event>&) const = 0;
	virtual bool isEventType(const std::shared_ptr<Event>& event) const = 0;
	virtual const int getID() const = 0;
};

template<typename EventType>
class EventListener : public BaseEventListener
{
public:
	using EventCallBackFn = std::function<void(const std::shared_ptr<EventType>&)>;
																						
	explicit EventListener(const EventCallBackFn& callBack, const int id) : callBack(callBack), id(id) { }
	const void dispatchEvent(const std::shared_ptr<Event>& event) const override { callBack(std::static_pointer_cast<EventType>(event)); }

	bool isEventType(const std::shared_ptr<Event>& event) const override { return std::dynamic_pointer_cast<EventType>(event) != nullptr; }

	const int getID() const override { return id; }

private:
	const EventCallBackFn callBack;
	const int id;
};