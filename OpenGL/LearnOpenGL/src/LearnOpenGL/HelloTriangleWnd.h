#pragma once

#include "FrameWnd.h"

class CHelloTriangleWnd : public frm::CFrameWnd
{
private:
	virtual void WindowProperty() override;
	virtual void Draw() override;
	
private:
	void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
};

