#pragma once

class ListenerID
{
public:
	explicit ListenerID(const int id) : id(id) { }
	
	int get() const { return id; }
	bool isRegisterd() const { return registered; }

	void unregister() { registered = false; }

private:
	const int id;
	bool registered = true;
};