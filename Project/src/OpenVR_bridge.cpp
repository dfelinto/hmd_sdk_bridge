#pragma once

#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <gl/glu.h>
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <iostream>

#include <openvr.h>

#include "shared/lodepng.h"
#include "shared/Matrices.h"
#include "shared/pathtools.h"

#include "OpenVR_bridge.h"


// using namespace vr;



typedef enum eLibStatus
{
	LIB_UNLOADED = 0,
	LIB_FAILED,
	LIB_INITIALIZED,
};

class DllExport OpenVRImpl : protected Backend
{
public:
	friend class OpenVRBridge;

	OpenVRImpl();
	~OpenVRImpl();

	bool setup(const unsigned int color_texture_left, const unsigned int color_texture_right);

	bool update(float *r_orientation_left, float *r_position_left, float *r_orientation_right, float *r_position_right);

	bool update(
		float *r_yaw_left, float *r_pitch_left, float *r_roll_left, float *r_position_left,
		float *r_yaw_right, float *r_pitch_right, float *r_roll_right, float *r_position_right);

	bool update(
		float *r_yaw_left, float *r_pitch_left, float *r_roll_left, float *r_orientation_left, float *r_position_left,
		float *r_yaw_right, float *r_pitch_right, float *r_roll_right, float *r_orientation_right, float *r_position_right);

	bool update(float *r_matrix_left, float *r_matrix_right);

	bool frameReady(void);

	bool reCenter(void);

	void getProjectionMatrixLeft(const float nearz, const float farz, const bool is_opengl, const bool is_right_hand, float *r_matrix);

	void getProjectionMatrixRight(const float nearz, const float farz, const bool is_opengl, const bool is_right_hand, float *r_matrix);

	

private:
	bool isConnected(void);
	unsigned int getProjectionMatrixFlags(const bool is_opengl, const bool is_right_hand);
	bool initializeLibrary(void);

	unsigned int m_frame;

	vr::IVRSystem *m_pHMDy;

	static eLibStatus m_lib_status;
	GLuint m_fbo[2];
};

eLibStatus OpenVRImpl::m_lib_status = LIB_UNLOADED;



bool OpenVRImpl::initializeLibrary()
{
	vr::EVRInitError eError;

	switch (OpenVRImpl::m_lib_status) {
	case LIB_FAILED:
		return false;
		break;
	case LIB_INITIALIZED:
		return true;
		break;
	case LIB_UNLOADED:
	default:
		/* try to load the library */
		// Loading the SteamVR Runtime
		vr::EVRInitError eError = vr::VRInitError_None;
		m_pHMDy = vr::VR_Init(&eError, vr::VRApplication_Scene);

		if (eError != vr::VRInitError_None)
		{
			m_pHMDy = NULL;
			char buf[1024];
			sprintf_s(buf, sizeof(buf), "Unable to init VR runtime: %s", vr::VR_GetVRInitErrorAsEnglishDescription(eError));
			// SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "VR_Init Failed", buf, NULL);
			return false;
		}
		return true;
		break;
	}

	return false;
}

OpenVRImpl::OpenVRImpl() :Backend()
{
	std::cout << "OpenVR()" << std::endl;

	/* we need glew to access opengl commands */
	glewInit();


	/* initialize data */
	this->m_frame = -1;
	this->m_fbo[0] = 0;
	this->m_fbo[1] = 0;

	std::cout << "OpenVR properly initialized (" << m_width[0] << "x" << m_height[0] << ", " << m_width[1] << "x" << m_height[1] << ")" << std::endl;
}

OpenVRImpl::~OpenVRImpl()
{
	std::cout << "~OpenVRImpl" << std::endl;
	for (int eye = 0; eye < 2; eye++) {
	}

}

bool OpenVRImpl::isConnected()
{
	return false;
}

bool OpenVRImpl::setup(const unsigned int color_texture_left, const unsigned int color_texture_right)
{
	// Make eye render buffers
	for (int eye = 0; eye < 2; eye++) {

	}

	std::cout << "OpenVR NOT properly setup." << std::endl;
	return true;
};

bool OpenVRImpl::update(float *r_orientation_left, float *r_position_left, float *r_orientation_right, float *r_position_right)
{
	return false;
};

bool OpenVRImpl::update(
	float *r_yaw_left, float *r_pitch_left, float *r_roll_left, float *r_position_left,
	float *r_yaw_right, float *r_pitch_right, float *r_roll_right, float *r_position_right)
{
	return false;
};

bool OpenVRImpl::update(
	float *r_yaw_left, float *r_pitch_left, float *r_roll_left, float *r_orientation_left, float *r_position_left,
	float *r_yaw_right, float *r_pitch_right, float *r_roll_right, float *r_orientation_right, float *r_position_right)
{
	return false;
}

bool OpenVRImpl::update(float *r_matrix_left, float *r_matrix_right)
{
	return false;
}

bool OpenVRImpl::frameReady()
{
	for (int eye = 0; eye < 2; eye++) {
		
	}

	return false;
};

bool OpenVRImpl::reCenter()
{
	return true;
};

void OpenVRImpl::getProjectionMatrixLeft(const float nearz, const float farz, const bool is_opengl, const bool is_right_hand, float *r_matrix)
{

}

void OpenVRImpl::getProjectionMatrixRight(const float nearz, const float farz, const bool is_opengl, const bool is_right_hand, float *r_matrix)
{

}

unsigned int OpenVRImpl::getProjectionMatrixFlags(const bool is_opengl, const bool is_right_hand)
{
	return 0;
}


// OpenVR Class
// -----------------------------------------------------------------

OpenVRBridge::OpenVRBridge()
	: Backend()
{	
}

OpenVRBridge::~OpenVRBridge()
{

}

bool OpenVRBridge::setup(const unsigned int color_texture_left, const unsigned int color_texture_right)
{
	return false;
}

bool OpenVRBridge::update(float *r_orientation_left, float *r_position_left, float *r_orientation_right, float *r_position_right)
{
	return false;
}

bool OpenVRBridge::update(
	float *r_yaw_left, float *r_pitch_left, float *r_roll_left, float *r_position_left,
	float *r_yaw_right, float *r_pitch_right, float *r_roll_right, float *r_position_right)
{
	return false;
}

bool OpenVRBridge::update(
	float *r_yaw_left, float *r_pitch_left, float *r_roll_left, float *r_orientation_left, float *r_position_left,
	float *r_yaw_right, float *r_pitch_right, float *r_roll_right, float *r_orientation_right, float *r_position_right)
{
	return false;
}

bool OpenVRBridge::update(float *r_matrix_left, float *r_matrix_right)
{
	return false;
}

bool OpenVRBridge::frameReady()
{
	return false;
}

bool OpenVRBridge::reCenter()
{
	return false;
}

void OpenVRBridge::getProjectionMatrixLeft(const float nearz, const float farz, const bool is_opengl, const bool is_right_hand, float *r_matrix)
{

}

void OpenVRBridge::getProjectionMatrixRight(const float nearz, const float farz, const bool is_opengl, const bool is_right_hand, float *r_matrix)
{

}

int OpenVRBridge::getWidthLeft()
{
	return 0;
}

int OpenVRBridge::getWidthRight()
{
	return 0;
}

int OpenVRBridge::getHeightLeft()
{
	return 0;
}

int OpenVRBridge::getHeightRight()
{
	return 0;
}

float OpenVRBridge::getScale()
{
	return 0.0f;
}

void OpenVRBridge::setScale(const float scale)
{
	
}