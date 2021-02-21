#pragma once
#include <vector>
#include "shader.h"
#include "vgestruct.h"
#include "vgebehaviour.h"
#include "mesh.h"
#include "scene.h"
#include "drawable.h"
#include "transform.h"
#include "vgetime.h"
#include "vgeinput.h"
#include "scenemanager.h"
//OpenGL related include
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/transform.hpp>
#include <gtc/quaternion.hpp>
#include <gtx/quaternion.hpp>

#define VGE_ENGINE_FPS_COUNTER_LIMIT 256

class VgeEngine
{
public:
	std::vector<Mesh> meshes;
	void Init(VgeGlfwData* vgeGlfwData, VgeBehaviour* vgeBehaviour, VgeAppData* vgeAppData);
	void CleanUp();
	void Run();
	void AddShader(Shader shader);
private:
	VgeBehaviour* vgeBehaviour;
	VgeAppData* vgeAppData;
	VgeGlfwData* vgeGlfwData;
	VgeEngineData vgeEngineData;
	void CompileShaders();
	void GameLoop();
	void Draw();
};

