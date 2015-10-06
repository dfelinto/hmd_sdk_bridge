#ifndef __HMD_H__
#define __HMD_H__

class HMD
{
public:
	HMD();
	~HMD();

/* must inherit */
	static bool isConnected();

	bool setup(const unsigned int framebuffer_object_left, const unsigned int framebuffer_object_right);

	bool update(float *r_head_transform[4][4], float *r_eye_left[3], float *r_eye_right[3]);

	bool frameReady(void);

	bool reCenter(void);

/* generic */
	int getWidth() { return this->m_width; }
	int getHeight() { return this->m_height; }
	void getProjectionMatrixLeft(const float nearz, const float farz, float *r_matrix[4][4]);
	void getProjectionMatrixRight(const float nearz, const float farz, float *r_matrix[4][4]);

protected:
	unsigned int m_framebuffer_object[2];
	unsigned int m_width;
	unsigned int m_height;
};


#endif /* __HMD_H__ */