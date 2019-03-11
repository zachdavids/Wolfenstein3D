#pragma once

#include <string>

class GLFWwindow;

class WindowManager
{
public:

	WindowManager();
	void Create(int width, int height, const std::string& title);
	void Destroy();
	void Render();
	bool CloseRequested();

	int GetWidth() { return width_; };
	int GetHeight() { return height_; };
	const std::string& GetTitle() { return title_; };
	void SetFullScreen(bool value);

private:

	int width_;
	int height_;
	std::string title_;
	GLFWwindow* window_;
};