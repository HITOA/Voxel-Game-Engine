#include "pch.h"
#include "vgeengine.h"

void VgeEngine::Init(VgeGlfwData* vgeGlfwData, VgeBehaviour* vgeBehaviour, VgeAppData* vgeAppData) {
	this->vgeAppData = vgeAppData;
	this->vgeGlfwData = vgeGlfwData;
	this->vgeBehaviour = vgeBehaviour;
	this->vgeBehaviour->Init();
	EnableGlFeatures();
	CompileShaders();
	Input::SetWindow(vgeGlfwData->window);
}

void VgeEngine::Run() {
	vgeBehaviour->Start();
	GameLoop();
}

void VgeEngine::AddShader(Shader shader)
{
	vgeEngineData.shaders.push_back(shader);
}

void VgeEngine::EnableGlFeatures()
{
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	glDepthFunc(GL_LESS);
}

void VgeEngine::CompileShaders()
{
	for (auto& shader : vgeEngineData.shaders) {
		shader.Init();
		shader.Compile();
	}
}

void VgeEngine::GameLoop() {
	double startFrameTime;
	double endFrameTime;
	double msFrameArray[VGE_ENGINE_FPS_COUNTER_LIMIT];
	int index = 0;
	do {
		Time::fixedTime = glfwGetTime();
		startFrameTime = Time::fixedTime;

		glClearColor(0.46, 0.7, 0.9, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Input::Update();

		vgeBehaviour->Update();
		Draw();

		glfwSwapBuffers(vgeGlfwData->window);

		endFrameTime = glfwGetTime();

		Time::deltaTime = (endFrameTime - startFrameTime);
		

		msFrameArray[index] = endFrameTime - startFrameTime;
		index++;

		if (index >= VGE_ENGINE_FPS_COUNTER_LIMIT) {
			index = 0;
			double result = 0;
			for (int i = 0; i < VGE_ENGINE_FPS_COUNTER_LIMIT; i++) {
				result += msFrameArray[i];
			}
			result /= VGE_ENGINE_FPS_COUNTER_LIMIT;
			printf("Average ms per frame (on %i frame) : %fms, (~%i fps)\n", VGE_ENGINE_FPS_COUNTER_LIMIT, result*1000, (int)(1/(result)));
		}

		glfwPollEvents();
	} while (!glfwWindowShouldClose(vgeGlfwData->window));
}

void VgeEngine::Draw()
{
	Camera* camera = SceneManager::GetScene()->GetCamera();

	glm::mat4 projection = camera->GetProjection(vgeAppData->wWidth, vgeAppData->wHeight);
	glm::mat4 view = camera->GetView();

	for (auto& entity : *SceneManager::GetScene()) {

		Transform* transform = nullptr;
		Drawable* drawable = nullptr;

		for (auto& component : *entity) {
			if (component->Type() == (int)ComponentType::Transform)
				transform = static_cast<Transform*>(component);
			if (component->Type() == (int)ComponentType::Drawable)
				drawable = static_cast<Drawable*>(component);
			if (transform && drawable)
				break;
		}

		if (transform && drawable) {
			glm::mat4 mvp = projection * view * transform->GetModel();

			vgeEngineData.shaders[0].SetActive();

			glUniformMatrix4fv(VGE_UNIFORM_MVP_POSITION, 1, GL_FALSE, &mvp[0][0]);

			drawable->mesh.Bind();

			glDrawElements(GL_TRIANGLES, drawable->mesh.indicies.size(), GL_UNSIGNED_SHORT, (void*)0);
		}
	}
}

void VgeEngine::CleanUp() {
	vgeEngineData.shaders.clear();
}