#pragma once

#include "Event.h"

#include <Stdint.h>

class KeyboardEvent : public Event
{
protected:
	KeyboardEvent(int keyCode, int scancode, int mods)
		: keyCode(keyCode), scancode(scancode), mods(mods) { }

public:
	int getKeyCode() const { return keyCode; }
	int getScanCode() const { return scancode; }
	int getMods() const { return mods; }

	EVENT_CATEGORY_FUNCTION(Keyboard)

private:
	int keyCode;
	int scancode;
	int mods;
};

class KeyboardPressEvent : public KeyboardEvent
{
public:
	KeyboardPressEvent(const int keyCode, const int scancode, const int mods)
		: KeyboardEvent(keyCode, scancode, mods){ }

	EVENT_TYPE_FUNCTION(KeyboardPress)
};

class KeyboardRepeat : public KeyboardEvent
{
	KeyboardRepeat(const int keyCode, const int scancode, const int mods)
		: KeyboardEvent(keyCode, scancode, mods) { }

	EVENT_TYPE_FUNCTION(KeyboardRepeat)
};

class KeyboardReleaseEvent : public KeyboardEvent
{
public:
	KeyboardReleaseEvent(const int keyCode, const int scancode, const int mods)
		: KeyboardEvent(keyCode, scancode, mods) { }

	EVENT_TYPE_FUNCTION(KeyboardRelease)
};

class CharPressEvent : public Event
{
public:
	CharPressEvent(const int codePoint)
		: codePoint(codePoint) { }

	const int getCodePoint() const { return codePoint; }

	const EventCategory getCategory() const override { return EventCategory::Keyboard; }
	EVENT_TYPE_FUNCTION(CharPress)

private:
	const int codePoint;
};