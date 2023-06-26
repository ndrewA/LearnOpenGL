#pragma once

#include <unordered_map>

class MouseState
{
public:
	struct Position
	{
		double x, y;
	};

	void keyDown(const int buttonCode) { buttons[buttonCode] = true; }
	void keyRelease(const int buttonCode) { buttons[buttonCode] = false; }
	void setPosition(Position position) { this->position = position; }

	bool isButtonDown(const int buttonCode) const { return buttons[buttonCode]; }
	Position getPosition() const { return position; }
private:
	mutable std::unordered_map<int, bool> buttons;
	Position position;
};