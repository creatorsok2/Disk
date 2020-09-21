#pragma once

#include "FrameWnd.h"

class CHelloTriangleWnd : public CFrameWnd
{
private:
	virtual void RegisterEventCallback() override;
	virtual void Draw() override;
	
private:
	void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
};

