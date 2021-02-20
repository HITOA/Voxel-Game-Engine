#pragma once
#include <vector>

class Component;

class Entity {
public:
	std::vector<Component*>::const_iterator begin() { return components.begin(); }
	std::vector<Component*>::const_iterator end() { return components.end(); }
	void AddComponent(Component* component);
private:
	std::vector<Component*> components;
};