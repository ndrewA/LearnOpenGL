#pragma once

#include <string>

#include "Events/WindowEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyboardEvent.h"

class Layer
{
public:
	Layer(const std::string& name)
		: name(name) { }
	virtual ~Layer() = default;

	virtual void update() = 0;
	virtual void onEvent(const Event& event) = 0;

	std::string getName() const { return name; }

private:
	std::string name;
};

class TestLayer : public Layer
{
public:
	void update() override { };
	void onEvent(const Event& event) override { };
};