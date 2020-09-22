#include "IncludeHeader.h"
#include "HelloTriangleWnd.h"

void CHelloTriangleWnd::WindowProperty()
{
	assert(window != nullptr && "not defined window");

	glfwSetWindowUserPointer(window, static_cast<void*>(this));
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* pWnd, int width, int height)
	{
		if (auto pFrameWnd = static_cast<CHelloTriangleWnd*>(glfwGetWindowUserPointer(pWnd)))
		{
			auto func = std::bind(&CHelloTriangleWnd::FrameBufferSizeCallback, pFrameWnd, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
			func(pWnd, width, height);
		}			
	});
}

void CHelloTriangleWnd::Draw()
{
	glClearColor(0.5f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void CHelloTriangleWnd::FrameBufferSizeCallback(GLFWwindow *, int width, int height)
{
	glViewport(0, 0, width, height);
}