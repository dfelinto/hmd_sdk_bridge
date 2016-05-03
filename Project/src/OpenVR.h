#ifndef __OPENVR_H__
#define __OPENVR_H__

#include "Backend.h"

#if defined(_WIN32) || defined(_WIN64)

#if !defined(DllExport)
#define DllExport   __declspec( dllexport )  
#endif

#else
#define DllExport
#endif

class DllExport OpenVR : public Backend
{
public:
	OpenVR();
	~OpenVR();

	bool setup(const unsigned int, const unsigned int);

	bool update(float *, float *, float *, float *);

	bool update(
		float *, float *, float *, float *,
		float *, float *, float *, float *);

	bool update(
		float *, float *, float *, float *, float *,
		float *, float *, float *, float *, float *);

	bool update(float *, float *);

	bool frameReady(void);

	bool reCenter(void);

	void getProjectionMatrixLeft(const float, const float, const bool, const bool, float *);

	void getProjectionMatrixRight(const float, const float, const bool, const bool, float *);

	virtual int getWidthLeft(void);
	virtual int getWidthRight(void);
	virtual int getHeightLeft(void);
	virtual int getHeightRight(void);
	virtual float getScale(void);
	virtual void setScale(const float scale);
private:
	class OpenVRImpl *m_me;
};

#endif /* __OPENVR_H__ */