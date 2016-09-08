#ifndef __BACKEND_H__
#define __BACKEND_H__

#if defined(_WIN32) || defined(_WIN64)

#if !defined(DllExport)
#define DllExport   __declspec( dllexport )  
#endif

#else
#define DllExport
#endif

class DllExport BackendImpl
{
public:
	BackendImpl(){ m_scale = 1.0f; }
	~BackendImpl() {}

	/* must inherit */
	virtual bool setup(const unsigned int color_texture_left, const unsigned int color_texture_right) = 0;

	virtual bool update(float *r_orientation_left, float *r_position_left, float *r_orientation_right, float *r_position_right) = 0;

	virtual bool update(
		float *r_yaw_left, float *r_pitch_left, float *r_roll_left, float *r_position_left,
		float *r_yaw_right, float *r_pitch_right, float *r_roll_right, float *r_position_right) = 0;

	virtual bool update(
		float *r_yaw_left, float *r_pitch_left, float *r_roll_left, float *r_orientation_left, float *r_position_left,
		float *r_yaw_right, float *r_pitch_right, float *r_roll_right, float *r_orientation_right, float *r_position_right) = 0;

	virtual bool update(const bool is_right_hand, float *r_matrix_left, float *r_matrix_right) = 0;

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

protected:
	unsigned int m_color_texture[2];
	unsigned int m_width[2];
	unsigned int m_height[2];
	float m_scale;
};

class DllExport Backend
{
public:
	Backend() {
		//this->initializeImplementation();
	}

	~Backend() {
		if (this->m_me) {
			delete this->m_me;
		}
	}

	bool setup(const unsigned int color_texture_left, const unsigned int color_texture_right)
	{
		return this->m_me->setup(color_texture_left, color_texture_right);
	}

	bool update(float *r_orientation_left, float *r_position_left, float *r_orientation_right, float *r_position_right)
	{
		return this->m_me->update(r_orientation_left, r_position_left, r_orientation_right, r_position_right);
	}

	bool update(
		float *r_yaw_left, float *r_pitch_left, float *r_roll_left, float *r_position_left,
		float *r_yaw_right, float *r_pitch_right, float *r_roll_right, float *r_position_right)
	{
		return this->m_me->update(
			r_yaw_left, r_pitch_left, r_roll_left, r_position_left,
			r_yaw_right, r_pitch_right, r_roll_right, r_position_right);
	}

	bool update(
		float *r_yaw_left, float *r_pitch_left, float *r_roll_left, float *r_orientation_left, float *r_position_left,
		float *r_yaw_right, float *r_pitch_right, float *r_roll_right, float *r_orientation_right, float *r_position_right)
	{
		return this->m_me->update(
			r_yaw_left, r_pitch_left, r_roll_left, r_orientation_left, r_position_left,
			r_yaw_right, r_pitch_right, r_roll_right, r_orientation_right, r_position_right);
	}

	bool update(const bool is_right_hand, float *r_matrix_left, float *r_matrix_right)
	{
		return this->m_me->update(is_right_hand, r_matrix_left, r_matrix_right);
	}

	bool frameReady(void)
	{
		return this->m_me->frameReady();
	}

	bool reCenter(void)
	{
		return this->m_me->reCenter();
	}

	void getProjectionMatrixLeft(const float nearz, const float farz, const bool is_opengl, const bool is_right_hand, float *r_matrix)
	{
		return this->m_me->getProjectionMatrixLeft(nearz, farz, is_opengl, is_right_hand, r_matrix);
	}

	void getProjectionMatrixRight(const float nearz, const float farz, const bool is_opengl, const bool is_right_hand, float *r_matrix)
	{
		return this->m_me->getProjectionMatrixRight(nearz, farz, is_opengl, is_right_hand, r_matrix);
	}

	/* generic */
	int getWidthLeft()
	{
		return this->m_me->getWidthLeft();
	}

	int getWidthRight()
	{
		return this->m_me->getWidthRight();
	}

	int getHeightLeft()
	{
		return this->m_me->getHeightLeft();
	}

	int getHeightRight()
	{
		return this->m_me->getHeightRight();
	}

	float getScale()
	{
		return this->m_me->getScale();
	}

	void setScale(const float scale)
	{
		this->m_me->setScale(scale);
	}

protected:
	BackendImpl *m_me;

	/* must overwrite */
	virtual void initializeImplementation() = 0;
};

#endif /* __BACKEND_H__ */
