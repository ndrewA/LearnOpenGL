#pragma once

#include <functional>

#include "MouseEvent.h"
#include "KeyboardEvent.h"
#include "WindowEvent.h"
#include "ListenerID.h"

class BaseEventListener
{
public:
	virtual ~BaseEventListener() = default;
	virtual void dispatchEvent(const Event&) const = 0;
	virtual bool isEventType(const Event& event) const = 0;
	virtual ListenerID getID() const = 0;
};

template<typename EventType>
class EventListener : public BaseEventListener
{
public:
	using EventCallBackFn = std::function<void(const EventType&)>;

	explicit EventListener(const EventCallBackFn& callBack, const ListenerID& id) : callBack(callBack), id(id) { }
	void dispatchEvent(const Event& event) const override { callBack(static_cast<const EventType&>(event));}

	bool isEventType(const Event& event) const override { return dynamic_cast<const EventType*>(&event) != nullptr; }

	ListenerID getID() const override { return id; }

private:
	const EventCallBackFn callBack;
	const ListenerID id;
};