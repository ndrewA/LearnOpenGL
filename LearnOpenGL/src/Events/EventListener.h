#pragma once

#include <functional>

#include "MouseEvent.h"
#include "KeyboardEvent.h"
#include "WindowEvent.h"
#include "EventListenerID.h"

class BaseEventListener
{
public:
	virtual ~BaseEventListener() = default;
	virtual bool dispatchEvent(const Event&) const = 0;
	virtual bool isEventType(const Event& event) const = 0;
	virtual EventListenerID getID() const = 0;
};

template<typename EventType>
class EventListener : public BaseEventListener
{
public:
	using EventCallBackFn = std::function<bool(const EventType&)>;

	explicit EventListener(const EventCallBackFn& callBack, const EventListenerID& id) : callBack(callBack), id(id) { }
	bool dispatchEvent(const Event& event) const override  { return callBack(static_cast<const EventType&>(event)); }

	bool isEventType(const Event& event) const override { return dynamic_cast<const EventType*>(&event) != nullptr; }

	EventListenerID getID() const override { return id; }

private:
	EventCallBackFn callBack;
	EventListenerID id;
};