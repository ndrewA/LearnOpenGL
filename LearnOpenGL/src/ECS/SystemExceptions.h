#pragma once

#include <stdexcept>

class SystemNotFoundException : public std::runtime_error
{
public:
	SystemNotFoundException(const std::string& systemType)
		: std::runtime_error("System not found: " + systemType) {}
};

class SystemAlreadyAddedException : public std::runtime_error
{
public:
	SystemAlreadyAddedException(const std::string& systemType)
		: std::runtime_error("System is already added: " + systemType) {}
};