#pragma once

#include <string>

class CharState
{
public:
	void charDown(const int codePoint) { charsDown += static_cast<char>(codePoint); } // assumes codePoint correlates to a char
	void clear() { charsDown.clear(); }

	std::string getCharsDown() const { return charsDown; }

private:
	std::string charsDown;
};