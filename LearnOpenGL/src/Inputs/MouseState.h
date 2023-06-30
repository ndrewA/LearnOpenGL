#pragma once

#include <array>

#include "MouseButtonCodes.h"

class MouseState
{
public:
	struct Position
	{
		double x, y;
	};

	void keyDown(int buttonCode) { buttons[buttonCode] = true; }
	void keyRelease(int buttonCode) { buttons[buttonCode] = false; }
	void setPosition(Position position) { this->position = position; }

	bool isButtonDown(int buttonCode) const { return buttons[buttonCode]; }
	Position getPosition() const { return position; }

private:
	std::array<bool, MOUSE_BUTTON_LAST + 1> buttons;
	Position position = { 0, 0 };
};