
#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <gl/glu.h>
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <iostream>

#include <openvr.h>

#include "shared/lodepng.h"
#include "shared/Matrices.h"
#include "shared/pathtools.h"

#include "OpenVR_bridge.h"


// using namespace vr;

typedef enum eLibStatus
{
	LIB_UNLOADED = 0,
	LIB_FAILED,
	LIB_INITIALIZED,
};

class DllExport OpenVRImpl : protected Backend
{
public:
	friend class OpenVRBridge;

	OpenVRImpl();
	~OpenVRImpl();

	bool setup(const unsigned int color_texture_left, const unsigned int color_texture_right);

	bool update(float *r_orientation_left, float *r_position_left, float *r_orientation_right, float *r_position_right);

	bool update(
		float *r_yaw_left, float *r_pitch_left, float *r_roll_left, float *r_position_left,
		float *r_yaw_right, float *r_pitch_right, float *r_roll_right, float *r_position_right);

	bool update(
		float *r_yaw_left, float *r_pitch_left, float *r_roll_left, float *r_orientation_left, float *r_position_left,
		float *r_yaw_right, float *r_pitch_right, float *r_roll_right, float *r_orientation_right, float *r_position_right);

	bool update(float *r_matrix_left, float *r_matrix_right);

	bool frameReady(void);

	bool reCenter(void);

	void getProjectionMatrixLeft(const float nearz, const float farz, const bool is_opengl, const bool is_right_hand, float *r_matrix);

	void getProjectionMatrixRight(const float nearz, const float farz, const bool is_opengl, const bool is_right_hand, float *r_matrix);

	

private:
	bool isConnected(void);
	unsigned int getProjectionMatrixFlags(const bool is_opengl, const bool is_right_hand);
	bool initializeLibrary(void);
	bool initializeCompositor(void);
	bool initializeOverlay(void);
	Matrix4 ConvertSteamVRMatrixToMatrix4(const vr::HmdMatrix34_t &matPose);
	Matrix4 GetCurrentViewProjectionMatrix(vr::Hmd_Eye nEye);
	void UpdateHMDMatrixPose();

	unsigned int m_frame;
	vr::IVRSystem *m_pHMDy;
	vr::IVRRenderModels *m_pRenderModels;
	vr::IVRCompositor *m_pCompositor;
	vr::VROverlayHandle_t m_OverlayHandle;
	static eLibStatus m_lib_status;
	Matrix4 m_rMat4TrackedPose[vr::k_unMaxTrackedDeviceCount];
	Matrix4 m_rmat4DevicePose[ vr::k_unMaxTrackedDeviceCount ];
	Matrix4 m_mat4HMDPose;
	char m_rDevClassChar[vr::k_unMaxTrackedDeviceCount];   // for each device, a character representing its class
	vr::TrackedDevicePose_t m_rTrackedDevicePose[vr::k_unMaxTrackedDeviceCount];
	GLuint m_fbo[2];

};

eLibStatus OpenVRImpl::m_lib_status = LIB_UNLOADED;



bool OpenVRImpl::initializeLibrary()
{
	vr::EVRInitError eError;

	switch (OpenVRImpl::m_lib_status) {
	case LIB_FAILED:
		return false;
		break;
	case LIB_INITIALIZED:
		return true;
		break;
	case LIB_UNLOADED:
	default:
		/* try to load the library */
		// Loading the SteamVR Runtime
		vr::EVRInitError eError = vr::VRInitError_None;
		m_pHMDy = vr::VR_Init(&eError, vr::VRApplication_Scene);

		if (eError != vr::VRInitError_None)
		{
			m_pHMDy = NULL;
			char buf[1024];
			sprintf_s(buf, sizeof(buf), "Unable to init VR runtime: %s", vr::VR_GetVRInitErrorAsEnglishDescription(eError));
			// SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "VR_Init Failed", buf, NULL);
			return false;
		}
		return true;
		break;
	}

	return false;
}

bool OpenVRImpl::initializeCompositor() 
{
	this->m_pCompositor = vr::VRCompositor();

	if (!this->m_pCompositor)
	{
		return false;
	}
	return true;
}

bool OpenVRImpl::initializeOverlay()
{
	vr::EVROverlayError peError = vr::VROverlayError_None;

	if (vr::VROverlay())
	{
		peError = vr::VROverlay()->CreateOverlay("cdBridgeLibOverlay", "Blender HMD Bridge Overlay", &m_OverlayHandle);

		if (peError == vr::VROverlayError_None) return true;
		else 
		{
			std::string s = std::to_string((int)peError);
			std::cout << "Error: VROverlayError: #" << s << std::endl ;
		}
	}

	return false;
}

Matrix4 OpenVRImpl::ConvertSteamVRMatrixToMatrix4(const vr::HmdMatrix34_t &matPose)
{
	Matrix4 matrixObj(
		matPose.m[0][0], matPose.m[1][0], matPose.m[2][0], 0.0,
		matPose.m[0][1], matPose.m[1][1], matPose.m[2][1], 0.0,
		matPose.m[0][2], matPose.m[1][2], matPose.m[2][2], 0.0,
		matPose.m[0][3], matPose.m[1][3], matPose.m[2][3], 1.0f
		);
	return matrixObj;
}

void OpenVRImpl::UpdateHMDMatrixPose()
{
	if (!m_pHMDy)
		return;

	this->m_pCompositor->WaitGetPoses(m_rTrackedDevicePose, vr::k_unMaxTrackedDeviceCount, NULL, 0);

	int m_iValidPoseCount = 0;
	std::string m_strPoseClasses = "";
	

	for (int nDevice = 0; nDevice < vr::k_unMaxTrackedDeviceCount; ++nDevice)
	{
		if (m_rTrackedDevicePose[nDevice].bPoseIsValid)
		{
			m_iValidPoseCount++;
			m_rmat4DevicePose[nDevice] = ConvertSteamVRMatrixToMatrix4(m_rTrackedDevicePose[nDevice].mDeviceToAbsoluteTracking);
			if (m_rDevClassChar[nDevice] == 0)
			{
				switch (m_pHMDy->GetTrackedDeviceClass(nDevice))
				{
				case vr::TrackedDeviceClass_Controller:        m_rDevClassChar[nDevice] = 'C'; break;
				case vr::TrackedDeviceClass_HMD:               m_rDevClassChar[nDevice] = 'H'; break;
				case vr::TrackedDeviceClass_Invalid:           m_rDevClassChar[nDevice] = 'I'; break;
				case vr::TrackedDeviceClass_Other:             m_rDevClassChar[nDevice] = 'O'; break;
				case vr::TrackedDeviceClass_TrackingReference: m_rDevClassChar[nDevice] = 'T'; break;
				default:                                       m_rDevClassChar[nDevice] = '?'; break;
				}
			}
			m_strPoseClasses += m_rDevClassChar[nDevice];
		}
	}

	if (m_rTrackedDevicePose[vr::k_unTrackedDeviceIndex_Hmd].bPoseIsValid)
	{
		m_mat4HMDPose = m_rmat4DevicePose[vr::k_unTrackedDeviceIndex_Hmd].invert();
	}
}

OpenVRImpl::OpenVRImpl() 
	:Backend()
{
	std::cout << "OpenVR()" << std::endl;

	/* we need glew to access opengl commands */
	glewInit();


	/* initialize data */
	this->m_frame = -1;
	this->m_fbo[0] = 0;
	this->m_fbo[1] = 0;

	// ovr_GetFovTextureSize on a DK2 is 1182x1464 - hardcode for now.
	this->m_width[0] = 1182;
	this->m_width[1] = 1182;
	this->m_height[0] = 1464;
	this->m_height[1] = 1464;

	this->m_status = "Inside DLL - Constructor";

	/* We set to true and then check some things.  Each failed step is to set this to false */
	this->setStateBool(true);

	/* Make sure the library is loaded */
	if (this->initializeLibrary() == false) {
		
		this->setStatus ( "Error: OpenVR library could not initialize" );
		this->setStateBool(false);

		std::cout << this->getStatus() << std::endl;
	}

	if (this->initializeCompositor() == false) {
		this->setStatus("Compositor initialization failed.\n");
		this->setStateBool(false);

		std::cout << this->getStatus() << std::endl;
	}

	if (this->initializeOverlay() == false)
	{
		this->setStatus("Overlay initialization failed.\n");
		this->setStateBool(false);
	}


	this->m_status = "After Init Library, Compositor and Overlay";

	if (this->getStateBool())
	{
		this->setStatus("OpenVR properly initialized.\n");
		std::cout << "OpenVR properly initialized (" << m_width[0] << "x" << m_height[0] << ", " << m_width[1] << "x" << m_height[1] << ")" << std::endl;
	}

	
}

OpenVRImpl::~OpenVRImpl()
{
	std::cout << "~OpenVRImpl" << std::endl;
	for (int eye = 0; eye < 2; eye++) {
	}

}

bool OpenVRImpl::isConnected()
{
	return false;
}

bool OpenVRImpl::setup(const unsigned int color_texture_left, const unsigned int color_texture_right)
{
	this->m_color_texture[0] = color_texture_left;
	this->m_color_texture[1] = color_texture_right;

	for (int eye = 0; eye < 2; eye++) {
		glGenFramebuffers(1, &this->m_fbo[eye]);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, this->m_fbo[eye]);
		glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_color_texture[eye], 0);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	}


	// Old overlay code
	//GLuint unTexture = m_pFbo->texture();
	//GLuint unTexture = color_texture_left;
	//vr::Texture_t texture = { (void*)unTexture, vr::API_OpenGL, vr::ColorSpace_Auto };
	//vr::VROverlay()->SetOverlayTexture(m_OverlayHandle, &texture);


	// Focus
	this->m_pCompositor->CompositorBringToFront();


	std::cout << "OpenVR setup() inside BridgeLib.dll complete." << std::endl;
	return true;
};

bool OpenVRImpl::update(float *r_orientation_left, float *r_position_left, float *r_orientation_right, float *r_position_right)
{
	// seems like this is the only one used.
	return false;
};

bool OpenVRImpl::update(
	float *r_yaw_left, float *r_pitch_left, float *r_roll_left, float *r_position_left,
	float *r_yaw_right, float *r_pitch_right, float *r_roll_right, float *r_position_right)
{
	return false;
};

bool OpenVRImpl::update(
	float *r_yaw_left, float *r_pitch_left, float *r_roll_left, float *r_orientation_left, float *r_position_left,
	float *r_yaw_right, float *r_pitch_right, float *r_roll_right, float *r_orientation_right, float *r_position_right)
{
	return false;
}

bool OpenVRImpl::update(float *r_matrix_left, float *r_matrix_right)
{
	/*  Gets Tracking Data */
	vr::TrackedDevicePose_t rTrackedDevicePose[vr::k_unMaxTrackedDeviceCount];

	m_pHMDy->GetDeviceToAbsoluteTrackingPose(vr::TrackingUniverseSeated, 0.0f, 
		VR_ARRAY_COUNT(vr::k_unMaxTrackedDeviceCount) rTrackedDevicePose, vr::k_unMaxTrackedDeviceCount);

	for (uint32_t i = 0; i < vr::k_unMaxTrackedDeviceCount; i++) 
	{
		m_rMat4TrackedPose[i] = this->ConvertSteamVRMatrixToMatrix4(rTrackedDevicePose[i].mDeviceToAbsoluteTracking);
	}
	
	return true;
}

bool OpenVRImpl::frameReady()
{

	// We must call WaitGetPoses before the Compositor gets focus
	// The following member function includes for this...
	this->UpdateHMDMatrixPose();

	if (!this->m_pCompositor->CanRenderScene()) {
		// this->setStatus("CanRenderScene() returned false");
		std::cout << "CanRenderScene() returned false" << std::endl;
		return false;
	}
	vr::EVRCompositorError err = vr::VRCompositorError_None;

	/* Renders the Frame */
	for (int eye = 0; eye < 2; eye++)
	{
		vr::EVREye eEye = (vr::EVREye)eye;

		vr::Texture_t texture = { (void*)this->m_color_texture[eye], vr::API_OpenGL, vr::ColorSpace_Auto };

		vr::VRTextureBounds_t bounds;
		bounds.uMin = (eye == 0) ? 0.0f : 0.5f;
		bounds.uMax = (eye == 0) ? 0.5f : 1.0f;
		bounds.vMin = 0.f;
		bounds.vMax = 1.f;

		err = this->m_pCompositor->Submit(eEye, &texture, &bounds);

		if (err != vr::VRCompositorError_None)
		{
			printf("Compositor Submit error: %d\n", err);
			return false;
		}
		//else
		//{
		//	std::cout << "We got here and no error?!?!" << std::endl;
		//}
	}

	return true;
};

bool OpenVRImpl::reCenter()
{
	m_pHMDy->ResetSeatedZeroPose();
	return true;

};

void OpenVRImpl::getProjectionMatrixLeft(const float nearz, const float farz, const bool is_opengl, const bool is_right_hand, float *r_matrix)
{

}

void OpenVRImpl::getProjectionMatrixRight(const float nearz, const float farz, const bool is_opengl, const bool is_right_hand, float *r_matrix)
{

}

unsigned int OpenVRImpl::getProjectionMatrixFlags(const bool is_opengl, const bool is_right_hand)
{
	return 0;
}

Matrix4 OpenVRImpl::GetCurrentViewProjectionMatrix(vr::Hmd_Eye nEye)
{
	Matrix4 matMVP;
	if (nEye == vr::Eye_Left)
	{
	//	matMVP = m_mat4ProjectionLeft * m_mat4eyePosLeft * m_mat4HMDPose;
	}
	else if (nEye == vr::Eye_Right)
	{
	//	matMVP = m_mat4ProjectionRight * m_mat4eyePosRight *  m_mat4HMDPose;
	}

	return matMVP;
}





// OpenVRBridge Class
// -----------------------------------------------------------------

OpenVRBridge::OpenVRBridge()
	: Backend()
	, m_me(new OpenVRImpl)
{	
}

OpenVRBridge::~OpenVRBridge()
{
	if (this->m_me) {
		delete this->m_me;
	}
}

bool OpenVRBridge::setup(const unsigned int color_texture_left, const unsigned int color_texture_right)
{
	return this->m_me->setup(color_texture_left, color_texture_right);
}

bool OpenVRBridge::update(float *r_orientation_left, float *r_position_left, float *r_orientation_right, float *r_position_right)
{
	return this->m_me->update(r_orientation_left, r_position_left, r_orientation_right, r_position_right);
}

bool OpenVRBridge::update(
	float *r_yaw_left, float *r_pitch_left, float *r_roll_left, float *r_position_left,
	float *r_yaw_right, float *r_pitch_right, float *r_roll_right, float *r_position_right)
{
	return this->m_me->update(
		r_yaw_left, r_pitch_left, r_roll_left, r_position_left,
		r_yaw_right, r_pitch_right, r_roll_right, r_position_right);
}

bool OpenVRBridge::update(
	float *r_yaw_left, float *r_pitch_left, float *r_roll_left, float *r_orientation_left, float *r_position_left,
	float *r_yaw_right, float *r_pitch_right, float *r_roll_right, float *r_orientation_right, float *r_position_right)
{
	return this->m_me->update(
		r_yaw_left, r_pitch_left, r_roll_left, r_orientation_left, r_position_left,
		r_yaw_right, r_pitch_right, r_roll_right, r_orientation_right, r_position_right);
}

bool OpenVRBridge::update(float *r_matrix_left, float *r_matrix_right)
{
	return this->m_me->update(r_matrix_left, r_matrix_right);
}

bool OpenVRBridge::frameReady()
{
	return this->m_me->frameReady();
}

bool OpenVRBridge::reCenter()
{
	return this->m_me->reCenter();
}

void OpenVRBridge::getProjectionMatrixLeft(const float nearz, const float farz, const bool is_opengl, const bool is_right_hand, float *r_matrix)
{
	return this->m_me->getProjectionMatrixLeft(nearz, farz, is_opengl, is_right_hand, r_matrix);
}

void OpenVRBridge::getProjectionMatrixRight(const float nearz, const float farz, const bool is_opengl, const bool is_right_hand, float *r_matrix)
{
	return this->m_me->getProjectionMatrixRight(nearz, farz, is_opengl, is_right_hand, r_matrix);
}

int OpenVRBridge::getWidthLeft()
{
	return this->m_me->getWidthLeft();
}

int OpenVRBridge::getWidthRight()
{
	return this->m_me->getWidthRight();
}

int OpenVRBridge::getHeightLeft()
{
	return this->m_me->getHeightLeft();
}

int OpenVRBridge::getHeightRight()
{
	return this->m_me->getHeightRight();
}

float OpenVRBridge::getScale()
{
	return this->m_me->getScale();
}

void OpenVRBridge::setScale(const float scale)
{
	this->m_me->setScale(scale);
}

const char* OpenVRBridge::getStatus()
{
	return this->m_me->getStatus();
}

void OpenVRBridge::setStatus(const char* str)
{
	this->m_me->setStatus(str);
}

bool OpenVRBridge::getStateBool()
{
	return this->m_me->getStateBool();
}

void OpenVRBridge::setStateBool(bool b)
{
	this->m_me->setStateBool(b);
}

