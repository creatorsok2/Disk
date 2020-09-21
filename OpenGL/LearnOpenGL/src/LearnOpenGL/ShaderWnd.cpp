#include "ShaderWnd.h"

#include <assert.h>
#include <functional>

CShaderWnd::CShaderWnd()
	: ourShader("Shader\\3.3\\shader.vs.glsl", "Shader\\3.3\\shader.fs.glsl") 
	// build and compile our shader program
	// you can name your shader files however you like	
{
}

void CShaderWnd::RegisterEventCallback()
{
	assert(m_pWnd != nullptr && "not defined window");

	glfwSetWindowUserPointer(m_pWnd, static_cast<void*>(this));
	glfwSetFramebufferSizeCallback(m_pWnd, [](GLFWwindow* window, int width, int height)
	{
		if (auto pWnd = static_cast<CShaderWnd*>(glfwGetWindowUserPointer(window)))
		{
			auto func = std::bind(&CShaderWnd::FrameBufferSizeCallback, pWnd, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
			func(window, width, height);
		}
	});
}

void CShaderWnd::InitRender()
{
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	// glBindVertexArray(0);

}

void CShaderWnd::ReleaseRender()
{
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void CShaderWnd::Draw()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// render the triangle
	ourShader.use();
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void CShaderWnd::FrameBufferSizeCallback(GLFWwindow *, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}
