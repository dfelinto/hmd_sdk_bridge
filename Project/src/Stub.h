#ifndef __STUB_H__
#define __STUB_H__

#include "Backend.h"

#if defined(_WIN32) || defined(_WIN64)

#if !defined(DllExport)
#define DllExport   __declspec( dllexport )  
#endif

#else
#define DllExport
#endif

class DllExport Stub : public Backend
{
public:
	Stub();
	~Stub();

	bool setup(const unsigned int color_texture_left, const unsigned int color_texture_right) { return false;  }

	bool update(float *r_orientation_left, float *r_position_left, float *r_orientation_right, float *r_position_right) { return false; }

	bool update(
		float *r_yaw_left, float *r_pitch_left, float *r_roll_left, float *r_position_left,
		float *r_yaw_right, float *r_pitch_right, float *r_roll_right, float *r_position_right)
	{
		return false;
	}

	bool update(
		float *r_yaw_left, float *r_pitch_left, float *r_roll_left, float *r_orientation_left, float *r_position_left,
		float *r_yaw_right, float *r_pitch_right, float *r_roll_right, float *r_orientation_right, float *r_position_right)
	{
		return false;
	}

	bool update(float *r_matrix_left, float *r_matrix_right)
	{
		return false;
	}

	bool frameReady(void)
	{
		return false;
	}

	bool reCenter(void)
	{
		return false;
	}

	void getProjectionMatrixLeft(const float nearz, const float farz, const bool is_opengl, const bool is_right_hand, float *r_matrix) {}

	void getProjectionMatrixRight(const float nearz, const float farz, const bool is_opengl, const bool is_right_hand, float *r_matrix) {}
};

#endif /* __STUB_H__ */