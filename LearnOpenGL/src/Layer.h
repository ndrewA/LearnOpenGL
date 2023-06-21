#pragma once

#include <string>

#include "Events/WindowEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyboardEvent.h"

class Layer
{
public:
	virtual ~Layer() = default;

	virtual void update() = 0;
	virtual void onEvent(const Event& event) = 0;

	const std::string getName() const { return name; }

private:
	const std::string& name;
};

class TestLayer : public Layer
{
public:
	void update() override;
	void onEvent(const Event& event) override;
};

void TestLayer::update()
{

}

void TestLayer::onEvent(const Event& event)
{

}