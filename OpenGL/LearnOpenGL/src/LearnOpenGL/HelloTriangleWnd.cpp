#include "HelloTriangleWnd.h"
#include "IncludeOpenGL.h"

#include <assert.h>
#include <functional>

void CHelloTriangleWnd::RegisterEventCallback()
{
	assert(m_pWnd != nullptr && "not defined window");

	glfwSetWindowUserPointer(m_pWnd, static_cast<void*>(this));
	glfwSetFramebufferSizeCallback(m_pWnd, [](GLFWwindow* window, int width, int height)
	{
		if (auto pWnd = static_cast<CHelloTriangleWnd*>(glfwGetWindowUserPointer(window)))
		{
			auto func = std::bind(&CHelloTriangleWnd::FrameBufferSizeCallback, pWnd, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
			func(window, width, height);
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