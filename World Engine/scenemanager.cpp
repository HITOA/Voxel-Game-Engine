#include "pch.h"
#include "scenemanager.h"

Scene* SceneManager::scene = nullptr;

Scene* SceneManager::GetScene()
{
	return scene;
}

void SceneManager::LoadScene(Scene* scene)
{
	if (SceneManager::scene != nullptr)
		delete SceneManager::scene;

	SceneManager::scene = scene;
}
