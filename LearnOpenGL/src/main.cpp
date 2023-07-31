#pragma once

#include <iostream>

#include "NewECS/ComponentContext.h"

class Component1 { };
class Component2 { };
class Component3 { };
class Component4 { };

class System1 
{
public:
	void update(Component1, Component1) { }
};

class System2 
{
public:
	void update(Component2, Component2) { }
};

class System3 
{
public:
	void update(Component3, Component1) { }
};

class System4 
{
public:
	void update(Component4) { }
};

int main()
{
	ComponentContext<System1, System2, System3, System4> componentContext;
	Entity entity{ 0 };
	componentContext.addToEntity<Component1>(entity, { });
	auto& c = componentContext.getComponent<Component1>(entity);
	componentContext.removeFromEntity<Component1>(entity);
	componentContext.removeEntity(entity);
	return 0;
}