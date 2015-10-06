#ifndef __OCULUS_H__
#define __OCULUS_H__

#include "HMD.h"

class Oculus : public HMD
{
public:
	Oculus();
	~Oculus();

	static bool isConnected();

	bool setup(unsigned int framebuffer_object);

	bool update(float r_head_transform[4][4], float r_eye_left[3], float r_eye_right[3]);

	bool frameReady(void);

	bool reCenter(void);
};

#endif /* __OCULUS_H__ */