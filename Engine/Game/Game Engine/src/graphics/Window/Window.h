#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
class Window {

public:

	Window(int width, int height, const char* title);
	~Window();

	bool ShouldClose();

	void update(); 
	inline GLFWwindow* getWindow() { return window; }
private:

	int p_Height,
		p_Width;
	GLFWwindow* window;

};