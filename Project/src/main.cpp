#include "Bridge.h"
#include "Oculus.h"
//#include "../Include/Bridge_C_API.h"

extern "C" {
	/* Oculus wrapper */
	Oculus *Oculus_new(){ return new Oculus(); }
	bool Oculus_isConnected(){ return Oculus::isConnected(); }
	bool Oculus_setup(Oculus *oculus, const unsigned int framebuffer_object_left, const unsigned int framebuffer_object_right){ return oculus->setup(framebuffer_object_left, framebuffer_object_right); }
	bool Oculus_update(Oculus *oculus, float *r_head_transform[4][4], float *r_eye_left[3], float *r_eye_right[3]) { return oculus->update(r_head_transform, r_eye_left, r_eye_right); }
	bool Oculus_frameReady(Oculus *oculus) { return oculus->frameReady(); }
	bool Oculus_reCenter(Oculus *oculus) { return oculus->reCenter(); }

	unsigned int Oculus_width(Oculus *oculus) { return oculus->getWidth(); }
	unsigned int Oculus_height(Oculus *oculus) { return oculus->getHeight(); }
	void Oculus_projectionMatrixLeft(Oculus *oculus, const float nearz, const float farz, float *r_matrix[4][4]) { return oculus->getProjectionMatrixLeft(nearz, farz, r_matrix); }
	void Oculus_projectionMatrixRight(Oculus *oculus, const float nearz, const float farz, float *r_matrix[4][4]) { return oculus->getProjectionMatrixRight(nearz, farz, r_matrix); }
}

#if 1
int main()
{
	return 0;
}
#endif

#if 0
BOOL APIENTRY main( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
#endif

#if 0
The Bridge will have the following functions:
bridge.oculus.HMD.isConnected()
Check if the oculus device is connected.
(static method)
: return : status
: rtype : bool

bridge.HMD class
bridge.oculus.HMD class (bridge.HMD)
Main class

__init__()
    Initialize the device, raise bridge.exception if it gone amiss
__del__()
    There is no explicit quit function, instead, implement the destructor

projecton_matrix_left
    @property
    4x4 Matrix

projecton_matrix_right
    @property
    4x4 Matrix

width
    @property
    int

height
    @property
    int

setup(framebuffer_object)
    :param framebuffer_object : framebuffer object created externally
    : type framebuffer_object : GLuint
    : return : True if successfully setup
    : rtype : bool

update()
    Get fresh tracking data
    : return : (head transformation, eye_pose_left, eye_pose_right)
    : rtype : Tuple

    head transformation(4x4 Matrix)
	eye_poses_left(vector3)
	eye_poses_right(vector3)

frameReady()
    Dispatch the framebuffer object to the device

recenter()
    Re - center the viewer

#endif