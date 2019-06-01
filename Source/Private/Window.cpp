#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Window* Window::m_Instance;

Window* Window::Get()
{
	return m_Instance;
}

bool Window::Create(int width, int height)
{
	if (m_Instance) { return false; }
	m_Instance = this;

	m_Width = width;
	m_Height = height;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	m_Window = glfwCreateWindow(width, height, "Wolfenstein3D", nullptr, nullptr);
	if (!m_Window)
	{
		return false;
	}

	glfwMakeContextCurrent(m_Window);

	if (!gladLoadGLLoader((GLADloadproc(glfwGetProcAddress))))
	{
		return false;
	}

	//glEnable(GL_MULTISAMPLE);
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LEQUAL);
	//glEnable(GL_CULL_FACE);
	//glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	////glEnable(GL_FRAMEBUFFER_SRGB);
	////glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glViewport(0, 0, width, height);

	return true;
}

void Window::Clear() const
{
	glClearColor(1.0f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::SwapAndPoll() const
{
	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}

bool Window::IsCloseRequested() const
{
	return glfwWindowShouldClose(m_Window);
}

void Window::Destroy()
{
	glfwTerminate();
}

int Window::GetWidth() const
{
	return m_Width;
}

int Window::GetHeight() const
{
	return m_Height;
}

GLFWwindow* Window::GetWindow() const
{
	return m_Window;
}
