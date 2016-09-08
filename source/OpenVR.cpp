//#include "GL/glew.h"

#include "OpenVR_backend.h"

#include <iostream>
#include <assert.h>

class DllExport OpenVRImpl : public BackendImpl
{
public:
	friend class OpenVR;

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

	bool update(const bool is_right_hand, float *r_matrix_left, float *r_matrix_right);

	bool frameReady(void);

	bool reCenter(void);

	void getProjectionMatrixLeft(const float nearz, const float farz, const bool is_opengl, const bool is_right_hand, float *r_matrix);

	void getProjectionMatrixRight(const float nearz, const float farz, const bool is_opengl, const bool is_right_hand, float *r_matrix);

private:
	bool isConnected(void);
	unsigned int getProjectionMatrixFlags(const bool is_opengl, const bool is_right_hand);
	static bool initializeLibrary(void);

#if 0
	unsigned int m_frame;
	ovrSession m_hmd;
	ovrLayerEyeFov m_layer;

	ovrEyeRenderDesc m_eyeRenderDesc[2];
	ovrVector3f m_hmdToEyeViewOffset[2];
	TextureBuffer *m_eyeRenderTexture[2];
	DepthBuffer *m_eyeDepthBuffer[2];
	static eLibStatus m_lib_status;
	GLuint m_fbo[2];
#endif
};

bool OpenVRImpl::initializeLibrary()
{
	// TODO
	return false;
}

OpenVRImpl::OpenVRImpl() :BackendImpl()
{
	// TODO
}

OpenVRImpl::~OpenVRImpl()
{
	// TODO
	std::cout << "~OpenVRImpl" << std::endl;
}

bool OpenVRImpl::isConnected()
{
	// TODO
	return false;
}

bool OpenVRImpl::setup(const unsigned int color_texture_left, const unsigned int color_texture_right)
{
	// TODO
	return false;
};

bool OpenVRImpl::update(float *r_orientation_left, float *r_position_left, float *r_orientation_right, float *r_position_right)
{
	// TODO
	return false;
};

bool OpenVRImpl::update(
	float *r_yaw_left, float *r_pitch_left, float *r_roll_left, float *r_position_left,
	float *r_yaw_right, float *r_pitch_right, float *r_roll_right, float *r_position_right)
{
	// TODO
	return false;
};

bool OpenVRImpl::update(
	float *r_yaw_left, float *r_pitch_left, float *r_roll_left, float *r_orientation_left, float *r_position_left,
	float *r_yaw_right, float *r_pitch_right, float *r_roll_right, float *r_orientation_right, float *r_position_right)
{
	// TODO
	return false;
}

bool OpenVRImpl::update(const bool is_right_hand, float *r_matrix_left, float *r_matrix_right)
{
	// TODO
	return false;
}

bool OpenVRImpl::frameReady()
{
	// TODO
	return false;
};

bool OpenVRImpl::reCenter()
{
	// TODO
	return false;
};

void OpenVRImpl::getProjectionMatrixLeft(const float nearz, const float farz, const bool is_opengl, const bool is_right_hand, float *r_matrix)
{
	// TODO
}

void OpenVRImpl::getProjectionMatrixRight(const float nearz, const float farz, const bool is_opengl, const bool is_right_hand, float *r_matrix)
{
	// TODO
}

unsigned int OpenVRImpl::getProjectionMatrixFlags(const bool is_opengl, const bool is_right_hand)
{
	// TODO
	return 0;
}

void OpenVR::initializeImplementation() {
	m_me = new OpenVRImpl();
}
