#ifndef __HMD_H__
#define __HMD_H__

class HMD
{
public:
	HMD();
	~HMD();

	static bool isConnected();

	bool setup(unsigned int framebuffer_object);

	bool update(float r_head_transform[4][4], float r_eye_left[3], float r_eye_right[3]);

	bool frameReady(void);

	bool reCenter(void);

private:
	unsigned int m_framebuffer_object;
};


#endif /* __HMD_H__ */