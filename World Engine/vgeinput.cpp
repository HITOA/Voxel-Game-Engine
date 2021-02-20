#include "pch.h"
#include "vgeinput.h"

GLFWwindow* Input::window = nullptr;
float Input::lastX = 0;
float Input::lastY = 0;
bool Input::mouseLock = false;

int Input::GetKeyStat(int key)
{
	return glfwGetKey(window, key);
}

Vector2 Input::GetMousePos()
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	return Vector2(x, y);
}

Vector2 Input::GetMouse()
{
	Vector2 newPos = GetMousePos();
	return Vector2(newPos.x - lastX, newPos.y - lastY);
}

void Input::SetMousePos(Vector2 pos)
{
	glfwSetCursorPos(window, pos.x, pos.y);
}

void Input::MouseLocked(bool lock)
{
	mouseLock = lock;
}

void Input::MouseVisible(bool visible)
{
	if (!visible) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}
	else {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

void Input::SetWindow(GLFWwindow* window)
{
	Input::window = window;
}

void Input::Update()
{
	Vector2 newPos = GetMousePos();
	lastX = newPos.x;
	lastY = newPos.y;

	if (mouseLock) {
		int width, height;

		glfwGetWindowSize(window, &width, &height);
		glfwSetCursorPos(window, width / 2, height / 2);
	}
}
