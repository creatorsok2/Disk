#pragma once

#include "IncludeHeader.h"
#include "FrameWnd.h"

class CShaderWnd : public CFrameWnd
{
public:
	CShaderWnd();
	virtual ~CShaderWnd() = default;

private:
	virtual void RegisterEventCallback() override;
	virtual void InitRender() override;
	virtual void ReleaseRender() override;
	virtual void Draw() override;

private:
	void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);

private:
	Shader ourShader;
	unsigned int VBO, VAO;
};

