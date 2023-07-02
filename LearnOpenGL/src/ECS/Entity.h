#pragma once

struct Entity
{
	size_t index;

    bool operator<(const Entity& other) const { return index < other.index; }
};
