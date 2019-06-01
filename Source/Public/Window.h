#pragma once

struct GLFWwindow;

class Window
{
public:

	Window() = default;
	bool Create(int width, int height);
	void Clear() const;
	void SwapAndPoll() const;
	bool IsCloseRequested() const;
	void Destroy();
	static Window* Get();
	int GetWidth() const;
	int GetHeight() const;
	GLFWwindow* GetWindow() const;

private:
	
	int m_Width;
	int m_Height;
	static Window* m_Instance;
	GLFWwindow* m_Window = nullptr;
};