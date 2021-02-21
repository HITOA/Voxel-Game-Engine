#pragma once
#include "scene.h"

class SceneManager
{
public:
	static Scene* GetScene();
	static void LoadScene(Scene* scene);
private:
	static Scene* scene;
};

