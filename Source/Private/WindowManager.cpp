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

	m_Window = glfwCreateWindow(800, 600, "Wolfenstein Remastered", nullptr, nullptr);
	if (!m_Window) 
	{ 
		return false; 
	}

	glfwMakeContextCurrent(m_Window);

	if (!gladLoadGLLoader((GLADloadproc(glfwGetProcAddress)))) 
	{
		return false; 
	}

	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	//glEnable(GL_FRAMEBUFFER_SRGB);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glViewport(0, 0, 800, 600);
	
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
