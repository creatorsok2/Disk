//----------------------------------------------------------------------------------
// File:   shadowmapping.cpp
// Author: Rouslan Dimitrov
// Email:  sdkfeedback@nvidia.com
// 
// Copyright (c) 2007 NVIDIA Corporation. All rights reserved.
//
// TO  THE MAXIMUM  EXTENT PERMITTED  BY APPLICABLE  LAW, THIS SOFTWARE  IS PROVIDED
// *AS IS*  AND NVIDIA AND  ITS SUPPLIERS DISCLAIM  ALL WARRANTIES,  EITHER  EXPRESS
// OR IMPLIED, INCLUDING, BUT NOT LIMITED  TO, IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL  NVIDIA OR ITS SUPPLIERS
// BE  LIABLE  FOR  ANY  SPECIAL,  INCIDENTAL,  INDIRECT,  OR  CONSEQUENTIAL DAMAGES
// WHATSOEVER (INCLUDING, WITHOUT LIMITATION,  DAMAGES FOR LOSS OF BUSINESS PROFITS,
// BUSINESS INTERRUPTION, LOSS OF BUSINESS INFORMATION, OR ANY OTHER PECUNIARY LOSS)
// ARISING OUT OF THE  USE OF OR INABILITY  TO USE THIS SOFTWARE, EVEN IF NVIDIA HAS
// BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
//
//----------------------------------------------------------------------------------

// This sample shows an implementation of cascaded shadow maps.
// The important pieces of code are fairly commented, so you can jump straight to display();
// The main idea of cascaded shadow maps is to split the camera view frustum into several
// smaller frusta and then calculate a separate shadow map for each. This has the advantage
// that objects near the camera get more resolution of the shadow map and ones that are far
// away get less, in an attempt to provide an uniform error in screen space.

// This sample uses the following artwork:
// Palmtree model
// http://telias.free.fr/zipsz/models_3ds/plants/palm1.zip
//
// Terrain textures
// http://www.cc.gatech.edu/projects/large_models/gcanyon.html


#include "main.h"
#include "terrain.h"

using namespace nv;

struct obj_BoundingSphere
{
	vec3f center;
	float radius;
};

int cur_num_splits = 2;
int show_depth_tex = 0;
int shadow_type = 0;

Terrain *terrain;

int width = 1024;
int height = 768;
int depth_size = 2048;

GLuint depth_fb, depth_rb;
GLuint depth_tex_ar;
GLuint view_prog;
GLuint shad_single_prog;
GLuint shad_single_hl_prog;
GLuint shad_multi_prog;
GLuint shad_multi_noleak_prog;
GLuint shad_pcf_prog;
GLuint shad_pcf_trilin_prog;
GLuint shad_pcf_4tap_prog;
GLuint shad_pcf_8tap_prog;
GLuint shad_pcf_gaussian_prog;

frustum f[MAX_SPLITS];
float shad_cpm[MAX_SPLITS][16];

obj_BoundingSphere obj_BSphere[NUM_OBJECTS];

float split_weight = 0.75f;

void makeScene()
{
	terrain = new Terrain;
	if(!terrain->Load())
	{
		printf("Couldn't find terrain textures.\n");
		exit(0);
	}
	int td = terrain->getDim()/2;
	obj_BSphere[0].center = vec3f(-td, 50.0, -td);
	obj_BSphere[1].center = vec3f(-td, 50.0,  td);
	obj_BSphere[2].center = vec3f( td, 50.0,  td);
	obj_BSphere[3].center = vec3f( td, 50.0, -td);
	obj_BSphere[0].radius = 1.0f;
	obj_BSphere[1].radius = 1.0f;
	obj_BSphere[2].radius = 1.0f;
	obj_BSphere[3].radius = 1.0f;
}

// Compute the 8 corner points of the current view frustum
void updateFrustumPoints(frustum &f, vec3f &center, vec3f &view_dir)
{
	vec3f up(0.0f, 1.0f, 0.0f);
	vec3f right = cross(view_dir,up);

	vec3f fc = center + view_dir*f.fard;
	vec3f nc = center + view_dir*f.neard;

	right = normalize(right);
	up = normalize(cross(right, view_dir));

	// these heights and widths are half the heights and widths of
	// the near and far plane rectangles
	float near_height = tan(f.fov/2.0f) * f.neard;
	float near_width = near_height * f.ratio;
	float far_height = tan(f.fov/2.0f) * f.fard;
	float far_width = far_height * f.ratio;

	f.point[0] = nc - up*near_height - right*near_width;
	f.point[1] = nc + up*near_height - right*near_width;
	f.point[2] = nc + up*near_height + right*near_width;
	f.point[3] = nc - up*near_height + right*near_width;

	f.point[4] = fc - up*far_height - right*far_width;
	f.point[5] = fc + up*far_height - right*far_width;
	f.point[6] = fc + up*far_height + right*far_width;
	f.point[7] = fc - up*far_height + right*far_width;
}

// updateSplitDist computes the near and far distances for every frustum slice
// in camera eye space - that is, at what distance does a slice start and end
void updateSplitDist(frustum f[MAX_SPLITS], float nd, float fd)
{
	float lambda = split_weight;
	float ratio = fd/nd;
	f[0].neard = nd;

	for(int i=1; i<cur_num_splits; i++)
	{
		float si = i / (float)cur_num_splits;

		f[i].neard = lambda*(nd*powf(ratio, si)) + (1-lambda)*(nd + (fd - nd)*si);
		f[i-1].fard = f[i].neard * 1.005f;
	}
	f[cur_num_splits-1].fard = fd;
}

// this function builds a projection matrix for rendering from the shadow's POV.
// First, it computes the appropriate z-range and sets an orthogonal projection.
// Then, it translates and scales it, so that it exactly captures the bounding box
// of the current frustum slice
float applyCropMatrix(frustum &f)
{
	float shad_modelview[16];
	float shad_proj[16];
	float shad_crop[16];
	float shad_mvp[16];
	float maxX = -1000.0f;
    float maxY = -1000.0f;
	float maxZ;
    float minX =  1000.0f;
    float minY =  1000.0f;
	float minZ;

	matrix4<float> nv_mvp;
	vec4f transf;	
	
	// find the z-range of the current frustum as seen from the light
	// in order to increase precision
	glGetFloatv(GL_MODELVIEW_MATRIX, shad_modelview);
	nv_mvp.set_value(shad_modelview);
	
	// note that only the z-component is need and thus
	// the multiplication can be simplified
	// transf.z = shad_modelview[2] * f.point[0].x + shad_modelview[6] * f.point[0].y + shad_modelview[10] * f.point[0].z + shad_modelview[14];
	transf = nv_mvp*vec4f(f.point[0], 1.0f);
	minZ = transf.z;
	maxZ = transf.z;
	for(int i=1; i<8; i++)
	{
		transf = nv_mvp*vec4f(f.point[i], 1.0f);
		if(transf.z > maxZ) maxZ = transf.z;
		if(transf.z < minZ) minZ = transf.z;
	}
	// make sure all relevant shadow casters are included
	// note that these here are dummy objects at the edges of our scene
	for(int i=0; i<NUM_OBJECTS; i++)
	{
		transf = nv_mvp*vec4f(obj_BSphere[i].center, 1.0f);
		if(transf.z + obj_BSphere[i].radius > maxZ) maxZ = transf.z + obj_BSphere[i].radius;
	//	if(transf.z - obj_BSphere[i].radius < minZ) minZ = transf.z - obj_BSphere[i].radius;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// set the projection matrix with the new z-bounds
	// note the inversion because the light looks at the neg. z axis
	// gluPerspective(LIGHT_FOV, 1.0, maxZ, minZ); // for point lights
	glOrtho(-1.0, 1.0, -1.0, 1.0, -maxZ, -minZ);
	glGetFloatv(GL_PROJECTION_MATRIX, shad_proj);
	glPushMatrix();
	glMultMatrixf(shad_modelview);
	glGetFloatv(GL_PROJECTION_MATRIX, shad_mvp);
	glPopMatrix();

	// find the extends of the frustum slice as projected in light's homogeneous coordinates
	nv_mvp.set_value(shad_mvp);
	for(int i=0; i<8; i++)
	{
		transf = nv_mvp*vec4f(f.point[i], 1.0f);

		transf.x /= transf.w;
		transf.y /= transf.w;

		if(transf.x > maxX) maxX = transf.x;
		if(transf.x < minX) minX = transf.x;
		if(transf.y > maxY) maxY = transf.y;
		if(transf.y < minY) minY = transf.y;
	}

	float scaleX = 2.0f/(maxX - minX);
	float scaleY = 2.0f/(maxY - minY);
	float offsetX = -0.5f*(maxX + minX)*scaleX;
	float offsetY = -0.5f*(maxY + minY)*scaleY;

	// apply a crop matrix to modify the projection matrix we got from glOrtho.
	nv_mvp.make_identity();
	nv_mvp.element(0,0) = scaleX;
	nv_mvp.element(1,1) = scaleY;
	nv_mvp.element(0,3) = offsetX;
	nv_mvp.element(1,3) = offsetY;
	transpose(nv_mvp);
	nv_mvp.get_value(shad_crop);
	glLoadMatrixf(shad_crop);
	glMultMatrixf(shad_proj);

	return minZ;
}

// here all shadow map textures and their corresponding matrices are created
void makeShadowMap()
{
	float shad_modelview[16];
//	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	// since the shadow maps have only a depth channel, we don't need color computation
	// glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	gluLookAt(0, 0, 0, -light_dir[0], -light_dir[1], -light_dir[2], -1.0f, 0.0f, 0.0f);
	glGetFloatv(GL_MODELVIEW_MATRIX, shad_modelview);

	// redirect rendering to the depth texture
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, depth_fb);
	// store the screen viewport
	glPushAttrib(GL_VIEWPORT_BIT);
	// and render only to the shadowmap
	glViewport(0, 0, depth_size, depth_size);
	// offset the geometry slightly to prevent z-fighting
	// note that this introduces some light-leakage artifacts
	glPolygonOffset( 1.0f, 4096.0f);
	glEnable(GL_POLYGON_OFFSET_FILL);

	// draw all faces since our terrain is not closed.
	glDisable(GL_CULL_FACE);

	// compute the z-distances for each split as seen in camera space
	updateSplitDist(f, 1.0f, FAR_DIST);

	// for all shadow maps:
	for(int i=0; i<cur_num_splits; i++)
	{
		// compute the camera frustum slice boundary points in world space
		updateFrustumPoints(f[i], vec3f(cam_pos), vec3f(cam_view));
		// adjust the view frustum of the light, so that it encloses the camera frustum slice fully.
		// note that this function sets the projection matrix as it sees best fit
		// minZ is just for optimization to cull trees that do not affect the shadows
		float minZ = applyCropMatrix(f[i]);
		// make the current depth map a rendering target
		glFramebufferTextureLayerEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, depth_tex_ar, 0, i);

		// clear the depth texture from last time
		glClear(GL_DEPTH_BUFFER_BIT);

		// draw the scene
		terrain->Draw(minZ);
		
		glMatrixMode(GL_PROJECTION);
		// store the product of all shadow matries for later
		glMultMatrixf(shad_modelview);
		glGetFloatv(GL_PROJECTION_MATRIX, shad_cpm[i]);
	}

	// revert to normal back face culling as used for rendering
	glEnable(GL_CULL_FACE);

	glDisable(GL_POLYGON_OFFSET_FILL);
	glPopAttrib(); 
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

	glEnable(GL_TEXTURE_2D);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void renderScene()
{
	float cam_proj[16];
	float cam_modelview[16];
	float cam_inverse_modelview[16];
	float far_bound[MAX_SPLITS];
	const float bias[16] = {	0.5f, 0.0f, 0.0f, 0.0f, 
								0.0f, 0.5f, 0.0f, 0.0f,
								0.0f, 0.0f, 0.5f, 0.0f,
								0.5f, 0.5f, 0.5f, 1.0f	};

	// approximate the atmosphere's filtering effect as a linear function
	float sky_color[4] = {0.8f, light_dir[1]*0.1f + 0.7f, light_dir[1]*0.4f + 0.5f, 1.0f};
	glClearColor(sky_color[0], sky_color[1], sky_color[2], sky_color[3]);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// update the camera, so that the user can have a free look
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	camLook();

	// store the inverse of the resulting modelview matrix for the shadow computation
	glGetFloatv(GL_MODELVIEW_MATRIX, cam_modelview);
	// since gluLookAt gives us an orthogonal matrix, we speed up the inverse computation
	cameraInverse(cam_inverse_modelview, cam_modelview);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)width/(double)height, f[0].neard, f[cur_num_splits-1].fard);
	glGetFloatv(GL_PROJECTION_MATRIX, cam_proj);

	// bind all depth maps
	glBindTexture(GL_TEXTURE_2D_ARRAY_EXT, depth_tex_ar);
    if (shadow_type >= 4) 
        glTexParameteri( GL_TEXTURE_2D_ARRAY_EXT, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
    else
        glTexParameteri( GL_TEXTURE_2D_ARRAY_EXT, GL_TEXTURE_COMPARE_MODE, GL_NONE);

    GET_GLERROR()

	for(int i=cur_num_splits; i<MAX_SPLITS; i++)
		far_bound[i] = 0;

	// for every active split
	for(int i=0; i<cur_num_splits; i++)
	{
		float light_m[16];

		// f[i].fard is originally in eye space - tell's us how far we can see.
		// Here we compute it in camera homogeneous coordinates. Basically, we calculate
		// cam_proj * (0, 0, f[i].fard, 1)^t and then normalize to [0; 1]
		far_bound[i] = 0.5f*(-f[i].fard*cam_proj[10]+cam_proj[14])/f[i].fard + 0.5f;

		// compute a matrix that transforms from camera eye space to light clip space
		// and pass it to the shader through the OpenGL texture matrices, since we
		// don't use them now
		glActiveTexture(GL_TEXTURE0 + (GLenum)i);
		glMatrixMode(GL_TEXTURE);
		glLoadMatrixf(bias);
		glMultMatrixf(shad_cpm[i]);
		// multiply the light's (bias*crop*proj*modelview) by the inverse camera modelview
		// so that we can transform a pixel as seen from the camera
		glMultMatrixf(cam_inverse_modelview);
		
		// compute a normal matrix for the same thing (to transform the normals)
		// Basically, N = ((L)^-1)^-t
		glGetFloatv(GL_TEXTURE_MATRIX, light_m);
		matrix4<float> nm;
		nm.set_value(light_m);
		nm = inverse(nm);
		nm = transpose(nm);

		glActiveTexture(GL_TEXTURE0 + (GLenum)(i+4));
		glMatrixMode(GL_TEXTURE);
		glLoadMatrixf(nm._array);
		
	}

	switch(shadow_type)
	{
	case 0:
		glUseProgram(shad_single_prog);
		glUniform1i(glGetUniformLocation(shad_single_prog, "stex"), 0); // depth-maps
		glUniform1i(glGetUniformLocation(shad_single_prog, "tex"), 1); // terrain tex
		// the shader needs to know the split distances, so that it can choose in which
		// texture to to the look up. Note that we pass them in homogeneous coordinates -
		// this the same space as gl_FragCoord is in. In this way the shader is more efficient
		glUniform4fv(glGetUniformLocation(shad_single_prog, "far_d"), 1, far_bound);
		break;
	case 1:
		glUseProgram(shad_single_hl_prog);
		glUniform1i(glGetUniformLocation(shad_single_hl_prog, "stex"), 0); // depth-maps
		glUniform1i(glGetUniformLocation(shad_single_hl_prog, "tex"), 1); // terrain tex
		glUniform4fv(glGetUniformLocation(shad_single_hl_prog, "far_d"), 1, far_bound);
		break;
	case 2:
		glUseProgram(shad_multi_prog);
		glUniform1i(glGetUniformLocation(shad_multi_prog, "stex"), 0); // depth-maps
		glUniform1i(glGetUniformLocation(shad_multi_prog, "tex"), 1); // terrain tex
		glUniform4fv(glGetUniformLocation(shad_multi_prog, "far_d"), 1, far_bound);
		break;
	case 3:
		glUseProgram(shad_multi_noleak_prog);
		glUniform1i(glGetUniformLocation(shad_multi_noleak_prog, "stex"), 0); // depth-maps
		glUniform1i(glGetUniformLocation(shad_multi_noleak_prog, "tex"), 1); // terrain tex
		glUniform4fv(glGetUniformLocation(shad_multi_noleak_prog, "far_d"), 1, far_bound);
		break;
    case 4:
        glUseProgram(shad_pcf_prog);
		glUniform1i(glGetUniformLocation(shad_pcf_prog, "stex"), 0); // depth-maps
		glUniform1i(glGetUniformLocation(shad_pcf_prog, "tex"), 1); // terrain tex
		glUniform4fv(glGetUniformLocation(shad_pcf_prog, "far_d"), 1, far_bound);
        glUniform2f(glGetUniformLocation(shad_pcf_prog, "texSize"), (float)depth_size, 1.0f/(float)depth_size);
		break;
    case 5:
        glUseProgram(shad_pcf_trilin_prog);
		glUniform1i(glGetUniformLocation(shad_pcf_trilin_prog, "stex"), 0); // depth-maps
		glUniform1i(glGetUniformLocation(shad_pcf_trilin_prog, "tex"), 1); // terrain tex
		glUniform4fv(glGetUniformLocation(shad_pcf_trilin_prog, "far_d"), 1, far_bound);
        glUniform2f(glGetUniformLocation(shad_pcf_trilin_prog, "texSize"), (float)depth_size, 1.0f/(float)depth_size);
		break;
    case 6:
        glUseProgram(shad_pcf_4tap_prog);
		glUniform1i(glGetUniformLocation(shad_pcf_4tap_prog, "stex"), 0); // depth-maps
		glUniform1i(glGetUniformLocation(shad_pcf_4tap_prog, "tex"), 1); // terrain tex
		glUniform4fv(glGetUniformLocation(shad_pcf_4tap_prog, "far_d"), 1, far_bound);
        glUniform2f(glGetUniformLocation(shad_pcf_4tap_prog, "texSize"), (float)depth_size, 1.0f/(float)depth_size);
		break;
    case 7:
        glUseProgram(shad_pcf_8tap_prog);
		glUniform1i(glGetUniformLocation(shad_pcf_8tap_prog, "stex"), 0); // depth-maps
		glUniform1i(glGetUniformLocation(shad_pcf_8tap_prog, "tex"), 1); // terrain tex
		glUniform4fv(glGetUniformLocation(shad_pcf_8tap_prog, "far_d"), 1, far_bound);
        glUniform2f(glGetUniformLocation(shad_pcf_8tap_prog, "texSize"), (float)depth_size, 1.0f/(float)depth_size);
		break;
    case 8:
        glUseProgram(shad_pcf_gaussian_prog);
		glUniform1i(glGetUniformLocation(shad_pcf_gaussian_prog, "stex"), 0); // depth-maps
		glUniform1i(glGetUniformLocation(shad_pcf_gaussian_prog, "tex"), 1); // terrain tex
		glUniform4fv(glGetUniformLocation(shad_pcf_gaussian_prog, "far_d"), 1, far_bound);
        glUniform2f(glGetUniformLocation(shad_pcf_gaussian_prog, "texSize"), (float)depth_size, 1.0f/(float)depth_size);
		break;
	}

	glLightfv(GL_LIGHT0, GL_POSITION, light_dir);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sky_color);
	glFogfv(GL_FOG_COLOR, sky_color);

	// finally, draw the scene 
	terrain->Draw();

	glUseProgram(0);

	GET_GLERROR()
}

// here we render the terrain from top and show the camera frusta.
// this display can be enabled from within the sample
void overviewCam()
{
	glActiveTexture(GL_TEXTURE0);
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	glDisable(GL_LIGHTING);
	glPointSize(10);
	glColor3f(1.0f, 1.0f, 0.0f);
	gluLookAt(0, FAR_DIST/2, 0, 0, 0, 0, 0, 0, 1.0f);

	glScalef(0.2f, 0.2f, 0.2f);
	glRotatef(20, 1, 0, 0);
	for(int i=0; i<cur_num_splits; i++)
	{
		glBegin(GL_LINE_LOOP);
		for(int j=0; j<4; j++)
			glVertex3f(f[i].point[j].x, f[i].point[j].y, f[i].point[j].z);

		glEnd();
		glBegin(GL_LINE_LOOP);
		for(int j=4; j<8; j++)
			glVertex3f(f[i].point[j].x, f[i].point[j].y, f[i].point[j].z);
		glEnd();
	}
	for(int j=0; j<4; j++)
	{
		glBegin(GL_LINE_STRIP);
		glVertex3fv(cam_pos);
		for(int i=0; i<cur_num_splits; i++)
			glVertex3f(f[i].point[j].x, f[i].point[j].y, f[i].point[j].z);
		glVertex3f(f[cur_num_splits-1].point[j+4].x, f[cur_num_splits-1].point[j+4].y, f[cur_num_splits-1].point[j+4].z);
		glEnd();
	}
	glLightfv(GL_LIGHT0, GL_POSITION, light_dir);
	glColor3f(0.9f, 0.9f, 1.0f);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	terrain->DrawCoarse();
}

// here we show all depth maps that have been generated for the current frame
// note that a special shader is required to display the depth-component-only textures
void showDepthTex()
{
	int loc;
	glPushAttrib(GL_VIEWPORT_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glUseProgram(view_prog);
	glUniform1i(glGetUniformLocation(view_prog,"tex"), 0);
	loc = glGetUniformLocation(view_prog,"layer");
	for(int i=0; i<cur_num_splits; i++)
	{
        glViewport(130*i, 0, 128, 128);
		glBindTexture(GL_TEXTURE_2D_ARRAY_EXT, depth_tex_ar);
        glTexParameteri( GL_TEXTURE_2D_ARRAY_EXT, GL_TEXTURE_COMPARE_MODE, GL_NONE);
		glUniform1f(loc, (float)i);
		glBegin(GL_QUADS);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glVertex3f( 1.0f, -1.0f, 0.0f);
		glVertex3f( 1.0f,  1.0f, 0.0f);
		glVertex3f(-1.0f,  1.0f, 0.0f);
		glEnd();

	}
	glUseProgram(0);

	glViewport(width - 129, 0, 128, 128);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);
	overviewCam();

	glEnable(GL_CULL_FACE);
	glPopAttrib();
}

// this is the main display function that glut calls for us. There are 2 main steps in the algorithm:
void display()
{
	updateKeys();

	// 1. Make the shadow map
	makeShadowMap();

	// 2. Render the world by applying the shadow maps
	renderScene();

	// additionally, we can display information to aid the understanding
	// of what is going on
	if(show_depth_tex)
		showDepthTex();

    glutSwapBuffers();
}

void init()
{
	glClearColor(0.8f, 0.8f , 0.9f, 1.0f);
	glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	makeScene();

	glGenFramebuffersEXT(1, &depth_fb);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, depth_fb);
	glDrawBuffer(GL_NONE);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

	glGenTextures(1, &depth_tex_ar);

	glBindTexture(GL_TEXTURE_2D_ARRAY_EXT, depth_tex_ar);
	glTexImage3D(GL_TEXTURE_2D_ARRAY_EXT, 0, GL_DEPTH_COMPONENT24, depth_size, depth_size, MAX_SPLITS, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D_ARRAY_EXT, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY_EXT, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY_EXT, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY_EXT, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY_EXT, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

	shad_single_prog = createShaders( "../../src/cascaded_shadow_maps/shadow_vertex.glsl", "../../src/cascaded_shadow_maps/shadow_single_fragment.glsl");
	shad_single_hl_prog = createShaders( "../../src/cascaded_shadow_maps/shadow_vertex.glsl", "../../src/cascaded_shadow_maps/shadow_single_hl_fragment.glsl");
	shad_multi_prog = createShaders( "../../src/cascaded_shadow_maps/shadow_vertex.glsl", "../../src/cascaded_shadow_maps/shadow_multi_leak_fragment.glsl");
	shad_multi_noleak_prog = createShaders( "../../src/cascaded_shadow_maps/shadow_vertex.glsl", "../../src/cascaded_shadow_maps/shadow_multi_noleak_fragment.glsl");
    shad_pcf_prog = createShaders( "../../src/cascaded_shadow_maps/shadow_vertex.glsl", "../../src/cascaded_shadow_maps/shadow_pcf_fragment.glsl");
    shad_pcf_trilin_prog = createShaders( "../../src/cascaded_shadow_maps/shadow_vertex.glsl", "../../src/cascaded_shadow_maps/shadow_pcf_trilinear_fragment.glsl");
    shad_pcf_4tap_prog = createShaders( "../../src/cascaded_shadow_maps/shadow_vertex.glsl", "../../src/cascaded_shadow_maps/shadow_pcf_4tap_fragment.glsl");
    shad_pcf_8tap_prog = createShaders( "../../src/cascaded_shadow_maps/shadow_vertex.glsl", "../../src/cascaded_shadow_maps/shadow_pcf_8tap_random_fragment.glsl");
    shad_pcf_gaussian_prog = createShaders( "../../src/cascaded_shadow_maps/shadow_vertex.glsl", "../../src/cascaded_shadow_maps/shadow_pcf_gaussian_fragment.glsl");

	view_prog = createShaders("../../src/cascaded_shadow_maps/view_vertex.glsl", "../../src/cascaded_shadow_maps/view_fragment.glsl");

	for(int i=0; i<MAX_SPLITS; i++)
	{
		// note that fov is in radians here and in OpenGL it is in degrees.
		// the 0.2f factor is important because we might get artifacts at
		// the screen borders.
		f[i].fov = 45.0/57.2957795 + 0.2f;
		f[i].ratio = (double)width/(double)height;
	}

	glFogf(GL_FOG_DENSITY, 0.4f);
	glFogf(GL_FOG_START, 16.0f);
	glFogf(GL_FOG_END, FAR_DIST);

    GET_GLERROR()
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayString("double rgb~8 depth~24 samples=4");
    glutInitWindowSize(width, height);
    glutCreateWindow("Cascaded Shadow Maps");

    glewInit();
    if (!glewIsSupported( "GL_VERSION_2_0 "))
	{
        printf( "Required extensions not supported.\n");
        return 1;
    }

    glutDisplayFunc(display);
    glutKeyboardFunc(keys);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
	glutMotionFunc(motion); 
	glutIdleFunc(idle);

	glutCreateMenu(menu);
	glutAddMenuEntry("SSM (1 split) [1]", '1');
	glutAddMenuEntry("CSM (2 split) [2]", '2');
	glutAddMenuEntry("CSM (3 split) [3]", '3');
	glutAddMenuEntry("CSM (4 split) [4]", '4');
	glutAddMenuEntry("Show Shadow Maps [`]", '`');
	glutAddMenuEntry("------------", '-1');
	glutAddMenuEntry("Normal Mode", 0);
	glutAddMenuEntry("Show Splits", 1);
	glutAddMenuEntry("Smooth shadows", 2);
	glutAddMenuEntry("Smooth shadows, no leak", 3);
    glutAddMenuEntry("PCF", 4);
    glutAddMenuEntry("PCF w/ trilinear", 5);
    glutAddMenuEntry("PCF w/ 4 taps", 6);
    glutAddMenuEntry("PCF w/ 8 random taps", 7);
    glutAddMenuEntry("PCF w/ gaussian blur", 8);
	glutAddMenuEntry("------------", '-1');
	glutAddMenuEntry("512x512", 10);
	glutAddMenuEntry("1024x1024", 11);
	glutAddMenuEntry("2048x2048", 12);
	glutAddMenuEntry("4096x4096", 13);
	glutAddMenuEntry("------------", '-1');
	glutAddMenuEntry("Exit [q]", 'q');
	glutAttachMenu(GLUT_RIGHT_BUTTON);

    init();

	printf("\nKeys:\n");
	printf("W, A, S, D        - move around\n");
	printf("Left Mouse Button - free look\n");
	printf("Shift + LMB       - move light\n");
	printf("1, 2, 3, 4        - number of splits\n");
	printf("~                 - show depth textures\n");

    glutMainLoop();
	
    return 0;
}
