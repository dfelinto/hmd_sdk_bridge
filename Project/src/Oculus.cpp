#include "Bridge.h"
#include "Oculus.h"
#include "HMD.h"
#include "OVR_CAPI_0_7_0.h"

#define MAX(a,b) a > b ? a : b;

Oculus::Oculus() :HMD()
{
	/* initialize the library */
	ovrResult result = ovr_Initialize(nullptr);
	if (OVR_FAILURE(result)) {
		throw "libOVR could not initialize";
	}

	ovrHmd hmd;
	ovrGraphicsLuid luid;

	/* initialize the device */
	result = ovr_Create(&hmd, &luid);
	if (OVR_FAILURE(result)) {
		ovr_Shutdown();
		throw "Oculus could not initialize";
	}

	ovrHmdDesc desc = ovr_GetHmdDesc(hmd);
	ovrSizei resolution = desc.Resolution;

	/* setup tracking system */
	ovr_ConfigureTracking(
		hmd,
		ovrTrackingCap_Orientation |
		ovrTrackingCap_MagYawCorrection |
		ovrTrackingCap_Position,
		0);

	/* store data */
	this->m_hmd = hmd;
	this->m_desc = desc;
	this->m_eyeRenderDesc[0] = ovr_GetRenderDesc(hmd, ovrEye_Left, desc.DefaultEyeFov[0]);
	this->m_eyeRenderDesc[1] = ovr_GetRenderDesc(hmd, ovrEye_Right, desc.DefaultEyeFov[1]);
	this->m_hmdToEyeViewOffset[0] = this->m_eyeRenderDesc[0].HmdToEyeViewOffset;
	this->m_hmdToEyeViewOffset[1] = this->m_eyeRenderDesc[1].HmdToEyeViewOffset;
	this->m_frame = -1;
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
	/* TODO */

	ovrSizei recommenedTex0Size = ovr_GetFovTextureSize(this->m_hmd, ovrEye_Left, this->m_desc.DefaultEyeFov[0], 1.0f);
	ovrSizei recommenedTex1Size = ovr_GetFovTextureSize(this->m_hmd, ovrEye_Right, this->m_desc.DefaultEyeFov[1], 1.0f);

	ovrSizei bufferSize;
	bufferSize.w = recommenedTex0Size.w + recommenedTex1Size.w;
	bufferSize.h = MAX(recommenedTex0Size.h, recommenedTex1Size.h);

	ovrLayerEyeFov layer;
	layer.Header.Type = ovrLayerType_EyeFov;
	layer.Header.Flags = 0;
	layer.ColorTexture[0] = /* TODO */ nullptr;
	layer.ColorTexture[1] = /* TODO */ nullptr;
	layer.Fov[0] = this->m_eyeRenderDesc[0].Fov;
	layer.Fov[1] = this->m_eyeRenderDesc[1].Fov;
	// /* TODO */ layer.Viewport[0] = ovrRecti(0, 0, bufferSize.w / 2, bufferSize.h);
	// /* TODO */ layer.Viewport[1] = ovrRecti(bufferSize.w / 2, 0, bufferSize.w / 2, bufferSize.h);

	/* store data */
	m_framebuffer_object = framebuffer_object;
	m_layer = layer;

	return true;
};

bool Oculus::update(float *r_head_transform[4][4], float *r_eye_left[3], float* r_eye_right[3])
{
	/* Get both eye poses simultaneously, with IPD offset already included */
	ovrFrameTiming ftiming = ovr_GetFrameTiming(this->m_hmd, ++this->m_frame);
	ovrTrackingState hmdState = ovr_GetTrackingState(this->m_hmd, ftiming.DisplayMidpointSeconds);

	ovr_CalcEyePoses(hmdState.HeadPose.ThePose, this->m_hmdToEyeViewOffset, this->m_layer.RenderPose);

	if ((hmdState.StatusFlags & (ovrStatus_OrientationTracked | ovrStatus_PositionTracked)) != 0) {
		/* TODO */

		this->m_layer.RenderPose[0].Position;
		this->m_layer.RenderPose[0].Orientation;
		this->m_layer.RenderPose[1].Position;
		this->m_layer.RenderPose[1].Orientation;

		return true;
	}
	return false;
};

bool Oculus::frameReady()
{
	ovrLayerHeader *layers = &this->m_layer.Header;
	ovrResult result = ovr_SubmitFrame(this->m_hmd, 0, nullptr, &layers, 1);

	if (ovrSuccess == result) {
		return true;
	}
	else{
		return false;
	}
};

bool Oculus::reCenter()
{
	ovr_RecenterPose(this->m_hmd);
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