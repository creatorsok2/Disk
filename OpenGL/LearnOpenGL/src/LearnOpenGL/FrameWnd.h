#pragma once

struct GLFWwindow;
class CFrameWnd
{
public:
	CFrameWnd();
	~CFrameWnd();

public:
	void RegisterEventCallback();
	void LoadOpenGLFunction();
	void RenderLoop();

public:
	void ProcessInput();
	void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);	

private:
	GLFWwindow* m_pWnd = nullptr;
	const int WND_WIDTH = 800;
	const int WND_HEIGHT = 600;
	
};

