#ifndef __BACKEND_H__
#define __BACKEND_H__

#include <string>

#if defined(_WIN32) || defined(_WIN64)

#if !defined(DllExport)
#define DllExport   __declspec( dllexport )  
#endif

#else
#define DllExport
#endif

class DllExport Backend
{
public:
	Backend() : m_scale(1.0), m_state_bool(false)  {}

	virtual ~Backend() {}

	/* must inherit */
	virtual bool setup(const unsigned int color_texture_left, const unsigned int color_texture_right) = 0;

	virtual bool update(float *r_orientation_left, float *r_position_left, float *r_orientation_right, float *r_position_right) = 0;

	virtual bool update(
		float *r_yaw_left, float *r_pitch_left, float *r_roll_left, float *r_position_left,
		float *r_yaw_right, float *r_pitch_right, float *r_roll_right, float *r_position_right) = 0;

	virtual bool update(
		float *r_yaw_left, float *r_pitch_left, float *r_roll_left, float *r_orientation_left, float *r_position_left,
		float *r_yaw_right, float *r_pitch_right, float *r_roll_right, float *r_orientation_right, float *r_position_right) = 0;

	virtual bool update(float *r_matrix_left, float *r_matrix_right) = 0;

	virtual bool frameReady(void) = 0;

	virtual bool reCenter(void) = 0;

	virtual void getProjectionMatrixLeft(const float nearz, const float farz, const bool is_opengl, const bool is_right_hand, float *r_matrix) = 0;

	virtual void getProjectionMatrixRight(const float nearz, const float farz, const bool is_opengl, const bool is_right_hand, float *r_matrix) = 0;

	/* generic */
	virtual int getWidthLeft() { return this->m_width[0]; }
	virtual int getHeightLeft() { return this->m_height[0]; }
	virtual int getWidthRight() { return this->m_width[1]; }
	virtual int getHeightRight() { return this->m_height[1]; }
	virtual float getScale() { return this->m_scale; }
	virtual void setScale(const float scale) { this->m_scale = scale; }
	virtual const char* getStatus() { return this->m_status.c_str(); }
	virtual void setStatus(const char* str) { this->m_status.assign(str); }
	virtual bool getStateBool() { return this->m_state_bool; }
	virtual void setStateBool(bool b) { this->m_state_bool = b; }

protected:
	unsigned int m_color_texture[2];
	unsigned int m_width[2];
	unsigned int m_height[2];
	float m_scale;
	std::string m_status;   // Holds a string to the last status - for debug/ui
	bool m_state_bool;      // Holds false if fatal error.
};

#endif /* __BACKEND_H__ */