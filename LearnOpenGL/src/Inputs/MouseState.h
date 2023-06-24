#pragma once

#include <unordered_map>

struct MousePosition
{
	double x, y;
};

class MouseState
{
public:
	void keyDown(const int buttonCode) { buttons[buttonCode] = true; }
	void keyRelease(const int buttonCode) { buttons[buttonCode] = false; }
	void setPosition(MousePosition position) { this->position = position; }

	bool isButtonDown(const int buttonCode) const { return buttons[buttonCode]; }
	MousePosition getPosition() const { return position; }
private:
	mutable std::unordered_map<int, bool> buttons;
	MousePosition position;
};