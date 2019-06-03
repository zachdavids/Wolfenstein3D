#pragma once

struct GLFWwindow;

class WindowManager
{
public:

	WindowManager() = default;
	bool Create(int width, int height);
	void Clear() const;
	void SwapAndPoll() const;
	bool IsCloseRequested() const;
	void Destroy();
	static WindowManager* Get() { return m_Instance; }
	GLFWwindow* GetWindow() const { return m_Window; }
	int GetWidth() { return m_Width; }
	int GetHeight() { return m_Height; }

private:

	int m_Width = 800;
	int m_Height = 600;
	static WindowManager* m_Instance;
	GLFWwindow* m_Window = nullptr;
};