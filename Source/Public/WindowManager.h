#pragma once

struct GLFWwindow;

class WindowManager
{
public:
	WindowManager() = default;
	bool Create();
	void Clear() const;
	void SwapAndPoll() const;
	bool IsCloseRequested() const;
	void Destroy();
	static WindowManager* Get() { return m_Instance; }
	GLFWwindow* GetWindow() const { return m_Window; }
private:
	static WindowManager* m_Instance;
	GLFWwindow* m_Window = nullptr;
};