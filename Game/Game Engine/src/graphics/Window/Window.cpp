#include "Window.h"

Window::Window(int width, int height, const char* title)
	:p_Width(width), p_Height(height)
{
	glewInit();
	glfwInit();
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	glfwSwapInterval(1);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwMakeContextCurrent(window);
}
Window::~Window()
{

}
bool Window::ShouldClose()
{
	glfwPollEvents();
	if (glfwWindowShouldClose(window))
		return true;
	return false;
}

void Window::update()
{
	glfwPollEvents();
	glfwSwapBuffers(window);
}