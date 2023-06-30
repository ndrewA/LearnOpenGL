#pragma once

#include <string>
#include <stdexcept>

class KeyNotFoundException : public std::runtime_error
{
public:
	KeyNotFoundException(int keyCode)
		: runtime_error("Key: " + std::to_string(keyCode) + " not found!") { }
};