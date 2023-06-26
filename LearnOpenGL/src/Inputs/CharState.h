#pragma once

#include <string>

class CharState
{
public:
	void charDown(const int codePoint) { charsDown += static_cast<char>(codePoint); } // TODO: make charsDown correlate to a codePoint
	void clear() { charsDown.clear(); }

	std::string getCharsDown() const { return charsDown; }

private:
	std::string charsDown;
};