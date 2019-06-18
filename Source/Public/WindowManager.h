#pragma once

struct GLFWwindow;

class WindowManager
{
public:

	WindowManager() = default;
	void Create();
	void Destroy() const;
	void InitGLFW();
	void InitWindow();
	void InitGlad();
	void Clear() const;
	void SwapAndPoll() const;
	bool IsCloseRequested() const;
	GLFWwindow* GetWindow() const;
	static WindowManager* Get();
	static constexpr int s_Width = 640;
	static constexpr int s_Height = 640;

private:

	GLFWwindow* m_Window = nullptr;
	static WindowManager* m_Instance;
};