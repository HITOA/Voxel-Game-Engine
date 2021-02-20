#include "pch.h"
#include "vgeinterface.h"

void VgeInterface::Init(VgeBehaviour* behaviour, VgeEngine* engine, VgeGlfwData* vgeGlfwData)
{
	this->behaviour = behaviour;
	this->engine = engine;
	this->behaviour->vgeInterface = this;
	this->vgeGlfwData = vgeGlfwData;
	this->scene = this->engine->GetScene();
}

void VgeInterface::SubmitShader(Shader shader)
{
	engine->AddShader(shader);
}

void VgeInterface::AddEntity(Entity* entity)
{
	scene->AddEntity(entity);
}

Camera* VgeInterface::GetCamera()
{
	return scene->GetCamera();
}

void VgeInterface::SetCamera(Camera* camera)
{
	scene->SetCamera(camera);
}

Scene* VgeInterface::GetScene()
{
	return scene;
}
