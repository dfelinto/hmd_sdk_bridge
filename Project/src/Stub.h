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
	bool setup(const unsigned int, const unsigned int) { return false;  }

	bool update(float *, float *, float *, float *) { return false; }

	bool update(
		float *, float *, float *, float *,
		float *, float *, float *, float *)
	{
		return false;
	}

	bool update(
		float *, float *, float *, float *, float *,
		float *, float *, float *, float *, float *)
	{
		return false;
	}

	bool update(float *, float *)
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

	void getProjectionMatrixLeft(const float, const float, const bool, const bool, float *) {}

	void getProjectionMatrixRight(const float, const float, const bool, const bool, float *) {}
};

#endif /* __STUB_H__ */