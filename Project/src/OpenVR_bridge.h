#ifndef __OPENVRBRIDGE_H__
#define __OPENVRBRIDGE_H__

#include "Backend.h"

#if defined(_WIN32) || defined(_WIN64)

#if !defined(DllExport)
#define DllExport   __declspec( dllexport )  
#endif

#else
#define DllExport
#endif

class DllExport OpenVRBridge : public Backend
{
public:
	OpenVRBridge();
	~OpenVRBridge();

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
	virtual const char* getStatus();
	virtual void setStatus(const char* str);
	virtual bool getStateBool();
	virtual void setStateBool(bool b);
private:
	class OpenVRImpl *m_me;
};

#endif /* __OPENVRBRIDGE_H__ */