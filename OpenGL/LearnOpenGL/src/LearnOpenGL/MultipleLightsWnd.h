#pragma once

#include "FrameWnd.h"

class CMultipleLightsWnd : public frm::CFrameWnd
{
	static float vertices[];
	static glm::vec3 cubePositions[];
	static glm::vec3 pointLightPositions[];

public:
	CMultipleLightsWnd();
	virtual ~CMultipleLightsWnd() = default;

private:
	virtual void WindowProperty() override;
	virtual void InitRender() override;
	virtual void ReleaseRender() override;
	virtual void PreDraw() override;
	virtual void Draw() override;
	virtual void ProcessInput() override;

private:
	void framebuffer_size_callback(GLFWwindow* pWnd, int width, int height);
	void mouse_callback(GLFWwindow* pWnd, double xpos, double ypos);
	void scroll_callback(GLFWwindow* pWnd, double xoffset, double yoffset);
	unsigned int loadTexture(const char *path);

private:
	Shader lightingShader;// ("6.multiple_lights.vs", "6.multiple_lights.fs");
	Shader lightCubeShader;//("6.light_cube.vs", "6.light_cube.fs");
	unsigned int VBO, cubeVAO;
	unsigned int lightCubeVAO;
	unsigned int diffuseMap;// = loadTexture("Resource/Image/container2.png");
	unsigned int specularMap;// = loadTexture("Resource/Image/container2_specular.png");

	// camera
	Camera camera;
	float lastX;
	float lastY;
	bool firstMouse;

	// timing
	float deltaTime;
	float lastFrame;

	// lighting
	glm::vec3 lightPos;//(1.2f, 1.0f, 2.0f);
};

