#pragma once
#include "vector2.h"

//OpenGL related include
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Input
{
public:
	static int GetKeyStat(int key);
	static Vector2 GetMousePos();
	static Vector2 GetMouse();
	static void SetMousePos(Vector2 pos);
	static void MouseLocked(bool lock);
	static void MouseVisible(bool visible);
	static void SetWindow(GLFWwindow* window);
	static void Update();
private:
	static GLFWwindow* window;
	static float lastX;
	static float lastY;
	static bool mouseLock;
};
