#include "pch.h"
#include "entity.h"
#include "component.h"

void Entity::AddComponent(Component* component)
{
	component->SetEntity(this);
	components.push_back(component);
}