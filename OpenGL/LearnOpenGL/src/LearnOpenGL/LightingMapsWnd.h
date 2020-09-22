#pragma once

#include "FrameWnd.h"
#include "learnopengl/camera.h"

class CLightingMapsWnd : public frm::CFrameWnd
{
	static float vertices[];
public:
	CLightingMapsWnd();
	virtual ~CLightingMapsWnd() = default;

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

	// build and compile our shader zprogram
	// ------------------------------------
	Shader lightingShader;// ("4.2.lighting_maps.vs", "4.2.lighting_maps.fs");
	Shader lightCubeShader;//("4.2.light_cube.vs", "4.2.light_cube.fs");
	unsigned int VBO, cubeVAO;
	unsigned int lightCubeVAO;
	unsigned int diffuseMap;// = loadTexture("Resource/Image/container2.png");
	unsigned int specularMap;// = loadTexture("Resource/Image/container2_specular.png");

	// camera
	Camera camera;// (glm::vec3(0.0f, 0.0f, 3.0f));
	float lastX;// = SCR_WIDTH / 2.0f;
	float lastY;// = SCR_HEIGHT / 2.0f;
	bool firstMouse;// = true;

	// timing
	float deltaTime;// = 0.0f;
	float lastFrame;// = 0.0f;

	// lighting
	glm::vec3 lightPos;//(1.2f, 1.0f, 2.0f);
};

