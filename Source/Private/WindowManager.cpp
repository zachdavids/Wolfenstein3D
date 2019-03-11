#include "WindowManager.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <assert.h>

WindowManager::WindowManager() {}

void WindowManager::Create(int width, int height, const std::string& title)
{
	width_ = width;
	height_ = height;
	title_ = title;

	assert(glfwInit());

	window_ = glfwCreateWindow(width_, height_, title_.c_str(), NULL, NULL);
	if (!window_) 
	{
		glfwTerminate();
	}

	glfwMakeContextCurrent(window_);
	glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Make the window's context the current one
	glfwMakeContextCurrent(window_);

	glewExperimental = GL_TRUE;
	assert(glewInit() == GLEW_OK);
}

void WindowManager::Destroy()
{
	glfwDestroyWindow(window_);
}

void WindowManager::Render()
{
	glfwSwapBuffers(window_);
}

bool WindowManager::CloseRequested()
{
	return glfwWindowShouldClose(window_);
}

void WindowManager::SetFullScreen(bool value)
{
	//TODO set fullscreen
}