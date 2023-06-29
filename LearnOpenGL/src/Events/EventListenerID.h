#pragma once

class EventListenerID
{
public:
	explicit EventListenerID(const size_t id) : id(id) { }
	
	size_t get() const { return id; }

private:
	const size_t id;
};