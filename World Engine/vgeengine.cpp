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
	glGenBuffers(1, &batchVBO);
	glGenBuffers(1, &batchIndiciesVBO);
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
	ComposeDrawQueue();

	Camera* camera = SceneManager::GetScene()->GetCamera();

	glm::mat4 projection = camera->GetProjection(vgeAppData->wWidth, vgeAppData->wHeight);
	glm::mat4 view = camera->GetView();

	unsigned int id = drawQueue[0].first;
	int count = 0;
	int verticesSize = 0;
	int colorsSize = 0;
	int normalsSize = 0;
	int uvSize = 0;
	int indiciesSize = 0;

	for (size_t i = 0; i < drawQueue.size(); i++) {
		if (id != drawQueue[i].first) {
			//Compose draw call
			if (count == 1) {
				glm::mat4 mvp = projection * view * drawQueue[i - 1].second.first->GetModel();

				drawQueue[i - 1].second.second->material->SetActive();

				glUniformMatrix4fv(VGE_UNIFORM_MVP_POSITION, 1, GL_FALSE, &mvp[0][0]);

				drawQueue[i - 1].second.second->mesh.Bind();

				glDrawElements(GL_TRIANGLES, drawQueue[i - 1].second.second->mesh.indicies.size(), GL_UNSIGNED_SHORT, (void*)0);
			}
			else {
				int fullSize = verticesSize + colorsSize + normalsSize + uvSize;

				glm::mat4 mvp = projection * view;

				drawQueue[i - 1].second.second->material->SetActive();

				glUniformMatrix4fv(VGE_UNIFORM_MVP_POSITION, 1, GL_FALSE, &mvp[0][0]);

				glBindBuffer(GL_ARRAY_BUFFER, batchVBO);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batchIndiciesVBO);

				glBufferData(GL_ARRAY_BUFFER, fullSize, NULL, GL_STREAM_DRAW);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiciesSize, NULL, GL_STREAM_DRAW);

				void* mvbo = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
				void* ivbo = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_WRITE);

				int verticiesOffset = 0;
				int colorsOffset = verticesSize;
				int normalsOffset = colorsOffset + colorsSize;
				int uvOffset = normalsOffset + normalsSize;
				int indiciesValueOffset = 0;
				int indiciesOffset = 0;

				glVertexAttribPointer(0,
					3,
					GL_FLOAT,
					GL_FALSE,
					0,
					(void*)verticiesOffset);

				glVertexAttribPointer(1,
					3,
					GL_FLOAT,
					GL_FALSE,
					0,
					(void*)colorsOffset);

				glVertexAttribPointer(2,
					3,
					GL_FLOAT,
					GL_FALSE,
					0,
					(void*)normalsOffset);

				glVertexAttribPointer(3,
					3,
					GL_FLOAT,
					GL_FALSE,
					0,
					(void*)uvOffset);

				for (int j = i - count; j < i; j++) {
					Mesh* current = &drawQueue[j].second.second->mesh;

					glm::mat4 model = drawQueue[j].second.first->GetModel();

					memcpy((char*)mvbo + verticiesOffset, current->vertices.data(), current->GetVerticiesBufferSize());

					float* vertex = (float*)((char*)mvbo + verticiesOffset);

					for (int i = 0; i < current->vertices.size(); i += 3) {
						glm::vec4 v = model * glm::vec4(vertex[i], vertex[i + 1], vertex[i + 2], 1);
						vertex[i] = v.x;
						vertex[i + 1] = v.y;
						vertex[i + 2] = v.z;
					}

					memcpy((char*)mvbo + colorsOffset, current->colors.data(), current->GetColorsBufferSize());
					memcpy((char*)mvbo + normalsOffset, current->normals.data(), current->GetNormalsBufferSize());
					memcpy((char*)mvbo + uvOffset, current->uv.data(), current->GetUvBufferSize());

					memcpy((char*)ivbo + indiciesOffset, current->indicies.data() , sizeof(uint16_t) * current->indicies.size());

					uint16_t* indice = (uint16_t*)((char*)ivbo + indiciesOffset);

					for (int i = 0; i < current->indicies.size(); i++) {
						indice[i] += indiciesValueOffset;
					}

					verticiesOffset += current->GetVerticiesBufferSize();
					colorsOffset += current->GetColorsBufferSize();
					normalsOffset += current->GetNormalsBufferSize();
					uvOffset += current->GetUvBufferSize();
					indiciesValueOffset += current->vertices.size() / 3;
					indiciesOffset += sizeof(uint16_t) * (current->indicies.size());
				}

				glUnmapBuffer(GL_ARRAY_BUFFER);
				glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);

				glDrawElements(GL_TRIANGLES, indiciesSize / sizeof(uint16_t), GL_UNSIGNED_SHORT, (void*)0);
			}

			id = drawQueue[i].first;
			count = 0;
			verticesSize = 0;
			colorsSize = 0;
			normalsSize = 0;
			uvSize = 0;
			indiciesSize = 0;
		}
		count++;
		if (i + 1 < drawQueue.size()) {
			verticesSize += drawQueue[i].second.second->mesh.GetVerticiesBufferSize();
			colorsSize += drawQueue[i].second.second->mesh.GetColorsBufferSize();
			normalsSize += drawQueue[i].second.second->mesh.GetNormalsBufferSize();
			uvSize += drawQueue[i].second.second->mesh.GetUvBufferSize();
			indiciesSize += sizeof(float) * (drawQueue[i].second.second->mesh.indicies.size());
		}
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void VgeEngine::ComposeDrawQueue()
{
	drawQueue.clear();
	//Check for each entity if it's drawable. if yes add to the queue with id composed of -> Material, Mesh?, probably some other things. and stock Drawable and Transform
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
			unsigned int id = (unsigned int)drawable->material;
			drawQueue.push_back(std::make_pair(id, std::make_pair(transform, drawable)));
		}
	}

	std::sort(drawQueue.begin(), drawQueue.end());
	drawQueue.push_back(std::make_pair(0, std::make_pair(nullptr, nullptr)));
}

void VgeEngine::CleanUp() {
	vgeEngineData.shaders.clear();
}