#pragma once

#include "Event.h"

#include <Stdint.h>

class KeyboardEvent : public Event
{
public:
	KeyboardEvent(const uint32_t keyCode) : keyCode(keyCode) { }
	virtual ~KeyboardEvent() = default;

	EVENT_CATEGORY_FUNCTION(Keyboard)

protected:
	uint32_t keyCode;
};

class KeyboardPressEvent : public KeyboardEvent
{
public:
	KeyboardPressEvent(uint32_t keyCode) : KeyboardEvent(keyCode) { }

	EVENT_TYPE_FUNCTION(KeyboardPress)
};

class KeyboardReleaseEvent : public KeyboardEvent
{
public:
	KeyboardReleaseEvent(uint32_t keyCode) : KeyboardEvent(keyCode) { }

	EVENT_TYPE_FUNCTION(KeyboardRelease)
};

class KeyPressEvent : public KeyboardEvent
{
public:
	KeyPressEvent(uint32_t keyCode) : KeyboardEvent(keyCode) { }

	EVENT_TYPE_FUNCTION(KeyPress)
};