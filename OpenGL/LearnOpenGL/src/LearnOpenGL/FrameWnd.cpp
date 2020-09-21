#include "FrameWnd.h"
#include "IncludeHeader.h"
#include "ProgramDirectory.h"

CFrameWnd::CFrameWnd()
{
	auto modulepath = CProgramDirectory::GetModuleDirectory();
	SetCurrentDirectory(modulepath.c_str());

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

	/* glad load all OpenGL function pointers */

	auto res = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	assert(res && "Failed to initialize GLAD");
}

CFrameWnd::~CFrameWnd()
{
	/* glfw terminated, clearning all previously allocated GLFW resources. */

	glfwTerminate();
}

void CFrameWnd::Run()
{
	if (m_pWnd == nullptr)
		return;

	RegisterEventCallback();

	InitRender();

	while (!glfwWindowShouldClose(m_pWnd))
	{
		// input
		ProcessInput();

		Draw();

		// check and call events and swap the buffers
		glfwSwapBuffers(m_pWnd);
		glfwPollEvents();
	}

	ReleaseRender();
}

void CFrameWnd::ProcessInput()
{
	if (glfwGetKey(m_pWnd, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_pWnd, true);
}