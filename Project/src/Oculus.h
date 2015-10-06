#ifndef __OCULUS_H__
#define __OCULUS_H__

#include "HMD.h"
#include "OVR_CAPI_0_7_0.h"

class Oculus : public HMD
{
public:
	Oculus();
	~Oculus();

	static bool isConnected();

	bool setup(unsigned int framebuffer_object);

	bool update(float *r_head_transform[4][4], float *r_eye_left[3], float *r_eye_right[3]);

	bool frameReady(void);

	bool reCenter(void);

	void getProjectionMatrixLeft(const float near, const float far, float *r_matrix[4][4]);
	void getProjectionMatrixRight(const float near, const float far, float *r_matrix[4][4]);

private:
	unsigned int m_frame;
	ovrHmd m_hmd;
	ovrHmdDesc m_desc;
	ovrEyeRenderDesc m_eyeRenderDesc[2];
	ovrVector3f m_hmdToEyeViewOffset[2];
	ovrLayerEyeFov m_layer;
};

#endif /* __OCULUS_H__ */