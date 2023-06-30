#pragma once

class EventListenerID
{
public:
	explicit EventListenerID(size_t id)  : id(id) { }

	size_t get() const { return id; }

private:
	size_t id;
};