#ifndef __OCULUS_H__
#define __OCULUS_H__

#include "HMD.h"
#include "OVR_CAPI_0_7_0.h"

typedef enum eLibStatus
{
	LIB_UNLOADED = 0,
	LIB_FAILED,
	LIB_INITIALIZED,
};

class Oculus : public HMD
{
public:
	Oculus();
	~Oculus();

	bool setup(const unsigned int framebuffer_object_left, const unsigned int framebuffer_object_right);

	bool update(float *r_orientation_left, float *r_position_left, float *r_orientation_right, float *r_position_right);

	bool frameReady(void);

	bool reCenter(void);

	void getProjectionMatrixLeft(const float nearz, const float farz, float *r_matrix);

	void getProjectionMatrixRight(const float nearz, const float farz, float *r_matrix);

	static bool initializeLibrary(void);

	bool mirrorOn(unsigned int *color_object, unsigned int *width, unsigned int *height);

	void mirrorOff(void);

private:
	bool isConnected(void);
	unsigned int m_frame;
	ovrHmd m_hmd;
	ovrHmdDesc m_desc;
	ovrEyeRenderDesc m_eyeRenderDesc[2];
	ovrVector3f m_hmdToEyeViewOffset[2];
	ovrLayerEyeFov m_layer;
	ovrSwapTextureSet *m_textureSet[2];

	static eLibStatus m_lib_status;
	unsigned int m_mirror_color_object;
	unsigned int m_mirror_framebuffer_object;
};

#endif /* __OCULUS_H__ */