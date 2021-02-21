#pragma once
#include <iostream>
#include <stdexcept>
#include <filesystem>

#include "vgestruct.h"
#include "vgeinterface.h"
#include "vgeengine.h"
#include "vgebehaviour.h"
//OpenGL related include
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define VGE_DEFAULT_WIDTH 0
#define VGE_DEFAULT_HEIGHT 0

#define VGE_NULL             0x0000
#define VGE_START_FULLSCREEN 0x0001

class VgeApp
{
public:
	VgeApp(VgeAppData vgeAppData);
	~VgeApp();
	void Init(VgeBehaviour* vgeBehaviour);
	void Run();
private:
	bool HasBeenInit;
	VgeInterface* vgeInterface;
	VgeAppData vgeAppData;
	VgeGlfwData vgeGlfwData;
	VgeEngine vgeEngine;
	void InitGlfw();
	void InitGlew();
	void InitWindow();
	//void InitInterface(VgeBehaviour* vgeBehaviour);
	void InitEngine(VgeBehaviour* vgeBehaviour);
};