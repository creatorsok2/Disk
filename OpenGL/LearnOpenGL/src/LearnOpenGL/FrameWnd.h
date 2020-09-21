#pragma once

struct GLFWwindow;

class CFrameWnd
{
public:
	CFrameWnd();
	virtual ~CFrameWnd();

public:
	void Run();

protected:
	virtual void RegisterEventCallback() {}
	virtual void InitRender() {}
	virtual void ReleaseRender() {}
	virtual void Draw() {}
	virtual void ProcessInput();

protected:
	GLFWwindow* m_pWnd = nullptr;
	const int WND_WIDTH = 800;
	const int WND_HEIGHT = 600;
	
};

