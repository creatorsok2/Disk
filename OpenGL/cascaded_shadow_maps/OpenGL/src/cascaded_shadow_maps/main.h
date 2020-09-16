// Email: sdkfeedback@nvidia.com
//
// Copyright (c) NVIDIA Corporation. All rights reserved.

#ifndef _MAIN_H_
#define _MAIN_H_

#define _CRT_SECURE_NO_DEPRECATE
#define _WIN32_LEAN_AND_MEAN

#include <stdlib.h>
#include <stdio.h>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <windows.h>

#include <nvMath.h>

struct frustum
{
	float neard;
	float fard;
	float fov;
	float ratio;
	nv::vec3f point[8];
};


#define FAR_DIST 200.0f
#define MAX_SPLITS 4
#define NUM_OBJECTS 4
#define LIGHT_FOV 45.0

void motion(int x, int y);
void mouse(int button, int state, int x, int y);
void idle();
void keys(unsigned char c, int x, int y);
void reshape(int w, int h);
void menu(int m);
void updateKeys();
void camLook();
void cameraInverse(float dst[16], float src[16]);
GLuint createShaders(char* vert, char* frag);
void CheckFramebufferStatus();

extern GLuint depth_tex_ar;;

extern float cam_pos[3];
extern float cam_view[3];
extern GLfloat light_dir[4];
extern int depth_size;
extern GLuint depth_tex_ar;

extern int width;
extern int height;

extern int cur_num_splits;
extern int show_depth_tex;
extern int shadow_type;
extern frustum f[MAX_SPLITS];

extern float split_weight;


#define GET_GLERROR()                                          \
{                                                                 \
    GLenum err = glGetError();                                    \
    if (err != GL_NO_ERROR) {                                     \
    fprintf(stderr, "[line %d] GL Error: %s\n",                \
    __LINE__, gluErrorString(err));                     \
    fflush(stderr);                                               \
    }                                                             \
}

#endif