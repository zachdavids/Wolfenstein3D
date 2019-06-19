#include "WindowManager.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

WindowManager* WindowManager::m_Instance;

void WindowManager::Create()
{
	if (m_Instance) { return; }
	m_Instance = this;

	InitGLFW();
	InitWindow();
	InitGlad();
}

void WindowManager::Clear() const
{
	glClearColor(0.49f, 0.49f, 0.49f, 1.0f);
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

void WindowManager::Destroy() const
{
	glfwTerminate();
}

void WindowManager::InitGLFW()
{
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
}

void WindowManager::InitWindow()
{
	m_Window = glfwCreateWindow(s_Width, s_Height, "Wolfenstein", nullptr, nullptr);
	glfwMakeContextCurrent(m_Window);
	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void WindowManager::InitGlad()
{
	gladLoadGLLoader((GLADloadproc(glfwGetProcAddress)));

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glViewport(0, 0, s_Width, s_Height);
}

WindowManager* WindowManager::Get()
{
	return m_Instance;
}

GLFWwindow* WindowManager::GetWindow() const
{
	return m_Window;
}
