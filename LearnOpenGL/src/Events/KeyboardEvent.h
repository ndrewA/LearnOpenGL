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

protected:
	int keyCode;
	int scancode;
	int mods;
};

class KeyboardPressEvent : public KeyboardEvent
{
public:
	KeyboardPressEvent(const int keyCode, const int scancode, const int mods, const int repeatCount)
		: KeyboardEvent(keyCode, scancode, mods), repeatCount(repeatCount) { }

	int getRepeatCount() const { return repeatCount; }

	EVENT_TYPE_FUNCTION(KeyboardPress)

private:
	int repeatCount;
};

class KeyboardReleaseEvent : public KeyboardEvent
{
public:
	KeyboardReleaseEvent(const int keyCode, const int scancode, const int mods, const int repeatCount)
		: KeyboardEvent(keyCode, scancode, mods) { }

	EVENT_TYPE_FUNCTION(KeyboardRelease)
};

class KeyPressEvent : public KeyboardEvent
{
public:
	KeyPressEvent(const int keyCode, const int scancode, const int mods, const int repeatCount)
		: KeyboardEvent(keyCode, scancode, mods) { }

	EVENT_TYPE_FUNCTION(KeyPress)
};