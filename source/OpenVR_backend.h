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

class OpenVRImpl;

class DllExport OpenVR : public Backend
{
protected:
	OpenVRImpl *m_me;
	virtual void initializeImplementation();
};

#endif /* __OPENVR_H__ */
