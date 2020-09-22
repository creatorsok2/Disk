#pragma once

#include <Windows.h>
#include <assert.h>
#include <functional>

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "learnopengl/shader_m.h"
#include "learnopengl/camera.h"
#include "learnopengl/model.h"

//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"