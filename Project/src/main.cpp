#include "Bridge.h"
#include "../Include/Bridge_C_API.h"

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