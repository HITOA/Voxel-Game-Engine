#pragma once
#include <vector>
#include <map>
#include "component.h"
#include "entity.h"
#include "camera.h"

class Scene
{
public:
	std::vector<Entity*>::const_iterator begin() { return entities.begin(); }
	std::vector<Entity*>::const_iterator end() { return entities.end(); }
	void AddEntity(Entity* entity);
	Camera* GetCamera();
	void SetCamera(Camera* camera);
private:
	Camera* camera;
	std::vector<Entity*> entities;
};

