#pragma once
#include "vgeengine.h"
#include "vgebehaviour.h"

class VgeInterface
{
public:
	void Init(VgeBehaviour* behaviour, VgeEngine* engine, VgeGlfwData* vgeGlfwData);
	void SubmitShader(Shader shader);
	void AddEntity(Entity* entity);
	Camera* GetCamera();
	void SetCamera(Camera* camera);
	Scene* GetScene();
private:
	VgeGlfwData* vgeGlfwData;
	VgeEngine* engine;
	VgeBehaviour* behaviour;
	Scene* scene;
};

