#ifndef __HMD_H__
#define __HMD_H__

#include "Backend.h"

#include "Oculus.h"
#include "OpenVR_bridge.h"
#include "Stub.h"


#if defined(_WIN32) || defined(_WIN64)

#if !defined(DllExport)
	#define DllExport   __declspec( dllexport )  
#endif

#else
#define DllExport
#endif

class DllExport HMD
{
public:

    enum eHMDBackend
	{
		BACKEND_OCULUS = 0,
		BACKEND_OCULUS_LEGACY,
		BACKEND_VIVE,
		BACKEND_OSVR,
		BACKEND_OPENVR,
		BACKEND_OPENHMD,
	};

	HMD(): m_hmd(new Oculus) {}

	HMD(eHMDBackend backend):
		m_hmd(nullptr)
	{
		switch (backend) {
			case BACKEND_OCULUS:
#if defined(_WIN32) || defined(_WIN64)
				m_hmd = new Oculus();
				break;
#endif
			case BACKEND_OPENVR:
				m_hmd = new OpenVRBridge();
				break;
			case BACKEND_VIVE:
				m_hmd = new OpenVRBridge();
				break;
			default:
				m_hmd = new Stub();
				break;
		}
	}

	~HMD(void) {
		if (m_hmd) {
			delete m_hmd;
		}
	}

	bool setup(const unsigned int color_texture_left, const unsigned int color_texture_right)
	{
		return m_hmd->setup(color_texture_left, color_texture_right);
	}

	bool update(float *r_orientation_left, float *r_position_left, float *r_orientation_right, float *r_position_right)
	{
		return m_hmd->update(r_orientation_left, r_position_left, r_orientation_right, r_position_right);
	}

	bool update(
		float *r_yaw_left, float *r_pitch_left, float *r_roll_left, float *r_position_left,
		float *r_yaw_right, float *r_pitch_right, float *r_roll_right, float *r_position_right)
	{
		return m_hmd->update(
			r_yaw_left, r_pitch_left, r_roll_left, r_position_left,
			r_yaw_right, r_pitch_right, r_roll_right, r_position_right);
	}

	bool update(
		float *r_yaw_left, float *r_pitch_left, float *r_roll_left, float *r_orientation_left, float *r_position_left,
		float *r_yaw_right, float *r_pitch_right, float *r_roll_right, float *r_orientation_right, float *r_position_right)
	{
		return m_hmd->update(
			r_yaw_left, r_pitch_left, r_roll_left, r_orientation_left, r_position_left,
			r_yaw_right, r_pitch_right, r_roll_right, r_orientation_right, r_position_right);
	}

	bool update(float *r_matrix_left, float *r_matrix_right) { return m_hmd->update(r_matrix_left, r_matrix_right); }

	bool frameReady(void) { return m_hmd->frameReady(); }

	bool reCenter(void) { return m_hmd->reCenter(); }

	void getProjectionMatrixLeft(const float nearz, const float farz, const bool is_opengl, const bool is_right_hand, float *r_matrix)
	{
		return m_hmd->getProjectionMatrixLeft(nearz, farz, is_opengl, is_right_hand, r_matrix);
	}

	void getProjectionMatrixRight(const float nearz, const float farz, const bool is_opengl, const bool is_right_hand, float *r_matrix)
	{
		return m_hmd->getProjectionMatrixRight(nearz, farz, is_opengl, is_right_hand, r_matrix);
	}

	/* generic */
	int getWidthLeft() { return m_hmd->getWidthLeft(); }
	int getHeightLeft() { return m_hmd->getHeightLeft(); }
	int getWidthRight() { return m_hmd->getWidthRight(); }
	int getHeightRight() { return m_hmd->getHeightRight(); }
	float getScale() { return m_hmd->getScale(); }
	void setScale(const float scale) { m_hmd->setScale(scale); }

	const char* getStatus() { return m_hmd->getStatus(); };
	bool getStateBool() { return m_hmd->getStateBool(); };

	

protected:
	Backend *m_hmd;
};

#endif /* __HMD_H__ */
