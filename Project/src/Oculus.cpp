#include "Bridge.h"
#include "Oculus.h"
#include "HMD.h"
#include "OVR_CAPI_0_7_0.h"

Oculus::Oculus() :HMD()
{
	/* initialize the library */
	ovrResult result = ovr_Initialize(nullptr);
	if (OVR_FAILURE(result)) {
		throw "libOVR could not initialize";
	}
}

Oculus::~Oculus()
{
	ovr_Destroy(this->m_hmd);
	ovr_Shutdown();
}

bool Oculus::isConnected()
{
	ovrHmdDesc desc = ovr_GetHmdDesc(nullptr);
	if (desc.AvailableHmdCaps) {
		return true;
	}
	else {
		return false;
	}
}

bool Oculus::setup(unsigned int framebuffer_object)
{
	m_framebuffer_object = framebuffer_object;

	ovrHmd hmd;
	ovrGraphicsLuid luid;

	/* initialize the device */
	ovrResult result = ovr_Create(&hmd, &luid);
	if (OVR_FAILURE(result)) {
		ovr_Shutdown();
		return false;
	}

	ovrHmdDesc desc = ovr_GetHmdDesc(hmd);
	ovrSizei resolution = desc.Resolution;

	this->m_hmd = hmd;
	this->m_eyeRenderDesc[0] = ovr_GetRenderDesc(hmd, ovrEye_Left, desc.DefaultEyeFov[0]);
	this->m_eyeRenderDesc[1] = ovr_GetRenderDesc(hmd, ovrEye_Right, desc.DefaultEyeFov[1]);

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

void Oculus::getProjectionMatrixLeft(const float near, const float far, float *r_matrix[4][4])
{
	ovrMatrix4f matrix = ovrMatrix4f_Projection(
		this->m_eyeRenderDesc[0].Fov,
		near,
		far,
		ovrProjection_RightHanded);

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			*r_matrix[i][j] = matrix.M[i][j];
}

void Oculus::getProjectionMatrixRight(const float near, const float far, float *r_matrix[4][4])
{
	ovrMatrix4f matrix = ovrMatrix4f_Projection(
		this->m_eyeRenderDesc[1].Fov,
		near,
		far,
		ovrProjection_RightHanded);

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			*r_matrix[i][j] = matrix.M[i][j];
}