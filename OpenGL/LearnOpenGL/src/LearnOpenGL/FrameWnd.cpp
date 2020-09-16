#include "FrameWnd.h"
#include "IncludeOpenGL.h"

#include <iostream>
#include <assert.h>


CFrameWnd::CFrameWnd()
{
	/* glfw initialize and configue */

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // __APPLE__

	/* glfw window creation */

	m_pWnd = glfwCreateWindow(WND_WIDTH, WND_HEIGHT, "LearnOpenGL", NULL, NULL);
	assert(m_pWnd != nullptr && "Failed to create window");

	if(m_pWnd)
		glfwMakeContextCurrent(m_pWnd);
}

CFrameWnd::~CFrameWnd()
{
	/* glfw terminated, clearning all previously allocated GLFW resources. */

	glfwTerminate();
}

void CFrameWnd::RegisterEventCallback()
{
	assert(m_pWnd != nullptr && "not defined window");

	glfwSetFramebufferSizeCallback(m_pWnd, [](GLFWwindow* window, int width, int height)
	{
		if(auto pWnd = static_cast<CFrameWnd*>(glfwGetWindowUserPointer(window)))
			pWnd->FrameBufferSizeCallback(window, width, height);
	});
}

void CFrameWnd::LoadOpenGLFunction()
{
	/* glad load all OpenGL function pointers */

	auto res = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	assert(res && "Failed to initialize GLAD");
}

void CFrameWnd::RenderLoop()
{
	/* render loop */

	while (!glfwWindowShouldClose(m_pWnd))
	{
		// input
		ProcessInput();

		// rendering command hear 
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// check and call events and swap the buffers
		glfwSwapBuffers(m_pWnd);
		glfwPollEvents();
	}
}

void CFrameWnd::ProcessInput()
{
	if (glfwGetKey(m_pWnd, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_pWnd, true);
}

void CFrameWnd::FrameBufferSizeCallback(GLFWwindow*, int width, int height)
{
	glViewport(0, 0, width, height);
}