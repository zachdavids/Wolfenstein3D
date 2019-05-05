#include "Window.h"

float Window::width_ = 0;
float Window::height_ = 0;
std::string Window::title_ = "Title";

void Window::Create(float width, float height, const std::string& title)
{
	Window::width_ = width;
	Window::height_ = height;
	Window::title_ = title;

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);

	SDL_ShowCursor(SDL_DISABLE);

	SDLCreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)width, (int)height, false);

	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
	}
}

void Window::Destroy()
{
	SDLDestroyWindow();
	SDL_Quit();
}

void Window::Render()
{
	SDLSwapBuffers();
}

bool Window::CloseRequested()
{
	return SDLGetIsCloseRequested();
}

void Window::SetFullScreen(bool value)
{
	SDLSetWindowFullscreen(value);
}