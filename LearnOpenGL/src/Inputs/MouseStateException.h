#pragma once

#include <string>
#include <stdexcept>

class MouseButtonNotFoundException : public std::runtime_error
{
public:
	MouseButtonNotFoundException(int buttonCode)
		: std::runtime_error(std::to_string(buttonCode) + " not found!") { }
};