#include "Bridge.h"
#include "Oculus.h"
#include "HMD.h"

Oculus::Oculus():HMD()
{
};

bool Oculus::isConnected()
{
	/* TODO */
	return true;
};

bool Oculus::setup(unsigned int framebuffer_object)
{
	m_framebuffer_object = framebuffer_object;
	/* TODO */
	return true;
};

bool Oculus::update(float r_head_transform[4][4], float r_eye_left[3], float r_eye_right[3])
{
	/* TODO */
	return true;
};

bool Oculus::frameReady()
{
	/* TODO */
	return true;
};

bool Oculus::reCenter()
{
	/* TODO */
	return true;
};