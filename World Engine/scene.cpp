#include "pch.h"
#include "scene.h"

void Scene::AddEntity(Entity* entity)
{
	entities.push_back(entity);
}

Camera* Scene::GetCamera()
{
	return camera;
}

void Scene::SetCamera(Camera* camera)
{
	this->camera = camera;
}
