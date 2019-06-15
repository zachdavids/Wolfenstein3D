#include "WindowManager.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

//TODO: Add JSON config file for Window setting

WindowManager* WindowManager::m_Instance;

bool WindowManager::Create()
{
	if (m_Instance) { return false; }
	m_Instance = this;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

	m_Window = glfwCreateWindow(640, 640, "Wolfenstein", nullptr, nullptr);
	if (!m_Window) 
	{ 
		return false; 
	}

	glfwMakeContextCurrent(m_Window);
	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	if (!gladLoadGLLoader((GLADloadproc(glfwGetProcAddress)))) 
	{
		return false; 
	}

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
	glViewport(0, 0, m_Width, m_Height);
	
	return true;
}

void WindowManager::Clear() const
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void WindowManager::SwapAndPoll() const
{
	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}

bool WindowManager::IsCloseRequested() const
{
	return glfwWindowShouldClose(m_Window);
}

void WindowManager::Destroy()
{
	glfwTerminate();
}
