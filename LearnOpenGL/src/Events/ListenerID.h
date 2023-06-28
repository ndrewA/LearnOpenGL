#pragma once

class ListenerID
{
public:
	explicit ListenerID(const size_t id) : id(id) { }
	
	size_t get() const { return id; }

private:
	const size_t id;
};