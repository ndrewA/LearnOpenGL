#pragma once

#include <string>

enum class EventCategory
{
	None,
	Input,
	Window,
	Mouse,
	Keyboard,
	Application,
};

enum class EventType
{
	None,
	WindowResize, WindowLostFocus, WindowGainedFocus, 
	WindowClose, WindowCursorEnter, WindowCursorLeave,
	MouseMove, MousePress, MouseRelease, MouseScroll,
	KeyboardPress, KeyboardRepeat, KeyboardRelease, CharPress,
};

struct EventDescription
{
	const EventType type;
	const std::string name;
	std::string origin;
};

class Event
{
public:
	virtual ~Event() = default;

	bool isHandeled() const { return handeled; }
	bool handle() { handeled = true; }

	EventType getType()			const { return getDescription().type; }
	std::string getTypeName()	const { return getDescription().name; }

	virtual EventDescription getDescription() const = 0;

private:
	bool handeled = false;
};									

class NoneEvent : public Event
{
public:
	EventDescription getDescription() const override { return { EventType::None, "None" }; }
};