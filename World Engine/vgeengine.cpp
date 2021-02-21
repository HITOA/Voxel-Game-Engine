#include "pch.h"
#include "vgeengine.h"

void VgeEngine::Init(VgeGlfwData* vgeGlfwData, VgeBehaviour* vgeBehaviour, VgeAppData* vgeAppData) {
	this->vgeAppData = vgeAppData;
	this->vgeGlfwData = vgeGlfwData;
	this->vgeBehaviour = vgeBehaviour;
	this->vgeBehaviour->Init();
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

void VgeEngine::CompileShaders()
{
	printf("%i\n", vgeEngineData.shaders.size());
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
		startFrameTime = glfwGetTime()*1000;

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		vgeBehaviour->Update();
		Draw();

		Input::Update();

		glfwSwapBuffers(vgeGlfwData->window);

		endFrameTime = glfwGetTime()*1000;
		Time::deltaTime = (endFrameTime - startFrameTime)/1000;
		

		msFrameArray[index] = endFrameTime - startFrameTime;
		index++;

		if (index >= VGE_ENGINE_FPS_COUNTER_LIMIT) {
			index = 0;
			double result = 0;
			for (int i = 0; i < VGE_ENGINE_FPS_COUNTER_LIMIT; i++) {
				result += msFrameArray[i];
			}
			result /= VGE_ENGINE_FPS_COUNTER_LIMIT;
			printf("Average ms per frame (on %i frame) : %fms, (~%i fps)\n", VGE_ENGINE_FPS_COUNTER_LIMIT, result, (int)(1/(result/1000)));
		}

		glfwPollEvents();
	} while (!glfwWindowShouldClose(vgeGlfwData->window));
}

void VgeEngine::Draw()
{
	Camera* camera = SceneManager::GetScene()->GetCamera();

	glm::mat4 projection = glm::perspective(glm::radians(camera->fov),
		(float)vgeAppData->wWidth / (float)vgeAppData->wHeight,
		camera->zNear,
		camera->zFar);

	glm::mat4 view = glm::inverse(glm::translate(glm::mat4(1.0f), glm::vec3(camera->transform.position.x, camera->transform.position.y, -camera->transform.position.z)) *
		glm::toMat4(glm::quat(glm::vec3(
		glm::radians(-camera->transform.rotation.x), 
		glm::radians(-camera->transform.rotation.y),
		glm::radians(-camera->transform.rotation.z)))));

	for (auto& entity : *SceneManager::GetScene()) {

		Transform* transform = nullptr;
		Drawable* drawable = nullptr;
		bool r = false;

		for (auto& component : *entity) {
			if (component->Type() == (int)ComponentType::Transform)
				transform = static_cast<Transform*>(component);
			if (component->Type() == (int)ComponentType::Drawable)
				drawable = static_cast<Drawable*>(component);
			if (transform != nullptr && drawable != nullptr) {
				r = true;
				break;
			}
		}

		if (r) {
			glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(transform->position.x, transform->position.y, transform->position.z)) *
				glm::toMat4(glm::quat(glm::vec3(
					glm::radians(transform->rotation.x),
					glm::radians(transform->rotation.y),
					glm::radians(transform->rotation.z)))) *
				glm::scale(glm::vec3(transform->scale.x, transform->scale.y, transform->scale.z));

			glm::mat4 mvp = projection * view * model;

			vgeEngineData.shaders[0].SetActive();

			glUniformMatrix4fv(vgeEngineData.shaders[0].GetMVP(), 1, GL_FALSE, &mvp[0][0]);
			glBindBuffer(GL_ARRAY_BUFFER, drawable->mesh.vbo);
			glVertexAttribPointer(0,
				3,
				GL_FLOAT,
				GL_FALSE,
				0,
				(void*)0);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
	}
}

void VgeEngine::CleanUp() {
	vgeEngineData.shaders.clear();
}