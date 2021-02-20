#include "pch.h"
#include "vge.h"

VgeApp::VgeApp(VgeAppData vgeAppData) {
	this->vgeAppData = vgeAppData;
	this->HasBeenInit == false;
	this->vgeInterface = new VgeInterface();
}

void VgeApp::Init(VgeBehaviour* vgeBehaviour) {
	InitGlfw();
	InitWindow();
	InitGlew();
	InitInterface(vgeBehaviour);
	InitEngine(vgeBehaviour);
	HasBeenInit = true;
}

void VgeApp::Run() {
	if (!HasBeenInit)
		throw std::runtime_error("VgeEngine can't run before initialization.");
	vgeEngine.Run();
}

void VgeApp::InitGlfw() {
	if (glfwInit() == GLFW_FALSE) {
		const char* description;
		glfwGetError(&description);

		if (description) {
			throw std::runtime_error(description);
		}
		else {
			throw std::runtime_error("Unknown error at GLFW initialization.");
		}
	}
}

void VgeApp::InitWindow() {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	vgeGlfwData.monitor = glfwGetPrimaryMonitor();

	if (vgeGlfwData.monitor == nullptr)
		throw std::runtime_error("Primary monitor not found.");

	if (vgeAppData.wWidth == VGE_DEFAULT_WIDTH)
		vgeAppData.wWidth = glfwGetVideoMode(vgeGlfwData.monitor)->width;
	if (vgeAppData.wHeight == VGE_DEFAULT_HEIGHT)
		vgeAppData.wHeight = glfwGetVideoMode(vgeGlfwData.monitor)->height;

	vgeGlfwData.window = glfwCreateWindow(vgeAppData.wWidth,
		vgeAppData.wHeight,
		vgeAppData.wName,
		vgeAppData.wAttrib & VGE_START_FULLSCREEN ? vgeGlfwData.monitor : nullptr,
		nullptr);

	if (vgeGlfwData.window == NULL) {
		const char* description;
		glfwGetError(&description);

		if (description) {
			throw std::runtime_error(description);
		}
		else {
			throw std::runtime_error("Unknown error at window creation.");
		}
	}

	glfwMakeContextCurrent(vgeGlfwData.window);

	glfwSwapInterval(0);
}

void VgeApp::InitGlew() {
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		throw std::runtime_error("Error at GLEW initialization.");
	}
}

void VgeApp::InitInterface(VgeBehaviour* vgeBehaviour) {
	vgeInterface->Init(vgeBehaviour, &vgeEngine, &vgeGlfwData);
}

void VgeApp::InitEngine(VgeBehaviour* vgeBehaviour) {
	vgeEngine.Init(&vgeGlfwData, vgeBehaviour, &vgeAppData);
}

VgeApp::~VgeApp() {
	vgeEngine.CleanUp();
	glfwDestroyWindow(vgeGlfwData.window);
	glfwTerminate();
}