#pragma once

#include "KeyCodes.h"

#include <array>

class KeyboardState
{
public:
	enum class ButtonState
	{
		Pressed,
		Repeated,
		Released,
	};

	KeyboardState() 
		: keyStates{ ButtonState::Released } { }

	void keyPress(int keyCode) { keyStates[keyCode] = ButtonState::Pressed; }
	void keyRepeat(int keyCode) { keyStates[keyCode] = ButtonState::Repeated; }
	void keyRelease(int keyCode) { keyStates[keyCode] = ButtonState::Released; }

	ButtonState getButtonState(int keyCode) const { return keyStates[keyCode]; }
	bool isKeyPressed(int keyCode) const { return keyStates[keyCode] == ButtonState::Pressed; }
	bool isKeyRepeated(int keyCode) const { return keyStates[keyCode] == ButtonState::Repeated; }
	bool isKeyReleased(int keyCode) const { return keyStates[keyCode] == ButtonState::Released; }

private:
	std::array<ButtonState, KEY_LAST + 1> keyStates;
};
