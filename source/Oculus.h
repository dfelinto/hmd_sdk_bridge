#ifndef __OCULUS_H__
#define __OCULUS_H__

#include "Backend.h"

#if defined(_WIN32) || defined(_WIN64)

#if !defined(DllExport)
#define DllExport   __declspec( dllexport )  
#endif

#else
#define DllExport
#endif

class OculusImpl;

class DllExport Oculus : public Backend
{
protected:
	OculusImpl *m_me;
	virtual void initializeImplementation();
};

#endif /* __OCULUS_H__ */
