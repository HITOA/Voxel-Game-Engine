#pragma once
#include "scene.h"

class Game
{
public:
	static Scene* GetScene();
private:
	static Scene* scene;
};

