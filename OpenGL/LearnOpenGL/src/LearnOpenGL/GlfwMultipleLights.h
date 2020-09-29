#pragma once

#include "GlfwFrame.h"

class GlfwMultipleLights : public ogl::GlfwFrame
{
public:
	GlfwMultipleLights();
	virtual ~GlfwMultipleLights();

private:
	virtual void build();
	virtual void draw();
	virtual void release();

};

