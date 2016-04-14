#include "Oculus.h"

#include "GL/glew.h"
#include "GL/wglew.h"

#include "OVR_CAPI_0_7_0.h"
#include "OVR_CAPI_GL.h"

#include "Extras/OVR_Math.h"
#include "Kernel/OVR_Log.h"

#include <iostream>

using namespace OVR;


#define MAX(a,b) a > b ? a : b;

struct TextureBuffer;

typedef enum eLibStatus
{
	LIB_UNLOADED = 0,
	LIB_FAILED,
	LIB_INITIALIZED,
};

class DllExport OculusImpl : protected Backend
{
public:
	friend class Oculus;

	OculusImpl();
	~OculusImpl();

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
	static bool initializeLibrary(void);

	unsigned int m_frame;
	ovrHmd m_hmd;
	ovrLayerEyeFov m_layer;

	ovrEyeRenderDesc m_eyeRenderDesc[2];
	ovrVector3f m_hmdToEyeViewOffset[2];
	TextureBuffer *m_eyeRenderTexture[2];
	static eLibStatus m_lib_status;
	GLuint m_fbo[2];
};

eLibStatus OculusImpl::m_lib_status = LIB_UNLOADED;

/* TextureBuffer copied/adapted from Oculus SDK samples */
struct TextureBuffer
{
	ovrHmd              hmd;
	ovrSwapTextureSet*  TextureSet;
	GLuint              fboId;
	Sizei               texSize;

	TextureBuffer(ovrHmd hmd, Sizei size, int sampleCount) :
		hmd(hmd),
		TextureSet(nullptr),
		fboId(0),
		texSize(0, 0)
	{
		OVR_ASSERT(sampleCount <= 1); // The code doesn't currently handle MSAA textures.

		texSize = size;

		// This texture isn't necessarily going to be a rendertarget, but it usually is.
		OVR_ASSERT(hmd); // No HMD? A little odd.
		OVR_ASSERT(sampleCount == 1); // ovr_CreateSwapTextureSetD3D11 doesn't support MSAA.

		ovrResult result = ovr_CreateSwapTextureSetGL(hmd, GL_SRGB8_ALPHA8, size.w, size.h, &TextureSet);

		if (OVR_SUCCESS(result)) {
			for (int i = 0; i < TextureSet->TextureCount; ++i) {
				ovrGLTexture* tex = (ovrGLTexture*)&TextureSet->Textures[i];
				glBindTexture(GL_TEXTURE_2D, tex->OGL.TexId);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}

			glGenFramebuffers(1, &fboId);
		}
	}

	~TextureBuffer()
	{
		if (TextureSet) {
			ovr_DestroySwapTextureSet(hmd, TextureSet);
			TextureSet = nullptr;
		}

		if (fboId) {
			glDeleteFramebuffers(1, &fboId);
			fboId = 0;
		}
	}

	Sizei GetSize() const
	{
		return texSize;
	}

	void SetAndClearRenderSurface()
	{
		auto tex = reinterpret_cast<ovrGLTexture*>(&TextureSet->Textures[TextureSet->CurrentIndex]);

		/* push attributes */
		glPushAttrib(GL_VIEWPORT_BIT | GL_SCISSOR_BIT);

		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fboId);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex->OGL.TexId, 0);

		glViewport(0, 0, texSize.w, texSize.h);
		glScissor(0, 0, texSize.w, texSize.h);
	}

	void UnsetRenderSurface()
	{
		/* pop attributes */
		glPopAttrib();

		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fboId);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 0, 0);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	}
};

bool OculusImpl::initializeLibrary()
{
	switch (OculusImpl::m_lib_status) {
	case LIB_FAILED:
		return false;
		break;
	case LIB_INITIALIZED:
		return true;
		break;
	case LIB_UNLOADED:
	default:
		/* try to load the library */
		break;
	}

	ovrResult result;
	result = ovr_Initialize(nullptr);

	if (OVR_FAILURE(result)) {
		OculusImpl::m_lib_status = LIB_FAILED;
		return false;
	}
	else {
		OculusImpl::m_lib_status = LIB_INITIALIZED;
		return true;
	}
}

OculusImpl::OculusImpl() :Backend()
{
	std::cout << "Oculus()" << std::endl;

	/* we need glew to access opengl commands */
	glewInit();

	/* Make sure the library is loaded */
	if (OculusImpl::initializeLibrary() == false) {
		std::cout << "libOVR could not initialize" << std::endl;
		throw "libOVR could not initialize";
	}

	if (this->isConnected() == false) {
		std::cout << "Oculus not connected" << std::endl;
		throw "Oculus not connected";
	}

	ovrHmd hmd;
	ovrGraphicsLuid luid;

	/* initialize the device */
	ovrResult result = ovr_Create(&hmd, &luid);
	if (OVR_FAILURE(result)) {
		ovr_Shutdown();
		std::cout << "Oculus could not initialize" << std::endl;
		throw "Oculus could not initialize";
	}

	ovrHmdDesc desc = ovr_GetHmdDesc(hmd);
	ovrSizei resolution = desc.Resolution;

	/* setup tracking system */
	ovr_ConfigureTracking(
		hmd,
		ovrTrackingCap_Orientation |
		ovrTrackingCap_MagYawCorrection |
		ovrTrackingCap_Position,
		0);

	ovrSizei recommendedTex0Size = ovr_GetFovTextureSize(hmd, ovrEye_Left, desc.DefaultEyeFov[0], 1.0f);
	ovrSizei recommendedTex1Size = ovr_GetFovTextureSize(hmd, ovrEye_Right, desc.DefaultEyeFov[1], 1.0f);

	/* initialize data */
	this->m_hmd = hmd;
	this->m_eyeRenderDesc[0] = ovr_GetRenderDesc(hmd, ovrEye_Left, desc.DefaultEyeFov[0]);
	this->m_eyeRenderDesc[1] = ovr_GetRenderDesc(hmd, ovrEye_Right, desc.DefaultEyeFov[1]);
	this->m_hmdToEyeViewOffset[0] = this->m_eyeRenderDesc[0].HmdToEyeViewOffset;
	this->m_hmdToEyeViewOffset[1] = this->m_eyeRenderDesc[1].HmdToEyeViewOffset;
	this->m_frame = -1;
	this->m_width[0] = recommendedTex0Size.w;
	this->m_height[0] = recommendedTex0Size.h;
	this->m_width[1] = recommendedTex1Size.w;
	this->m_height[1] = recommendedTex1Size.h;
	this->m_eyeRenderTexture[0] = NULL;
	this->m_eyeRenderTexture[1] = NULL;
	this->m_fbo[0] = 0;
	this->m_fbo[1] = 0;
	std::cout << "Oculus properly initialized (" << m_width[0] << "x" << m_height[0] << ", " << m_width[1] << "x" << m_height[1] << ")" << std::endl;
}

OculusImpl::~OculusImpl()
{
	std::cout << "~OculusImpl" << std::endl;

	for (int eye = 0; eye < 2; eye++) {
		if (this->m_eyeRenderTexture[eye])
			delete this->m_eyeRenderTexture[eye];

		if (this->m_fbo[eye])
			glDeleteFramebuffers(1, &this->m_fbo[eye]);
	}

	ovr_Destroy(this->m_hmd);
	ovr_Shutdown();

	/* the library needs to be re-loaded every time because the
	 * Python wrapper keeps the static values
	 */
	OculusImpl::m_lib_status = LIB_UNLOADED;
}

bool OculusImpl::isConnected()
{
	/* Make sure the library is loaded */
	if (OculusImpl::initializeLibrary() == false)
		throw "libOVR could not initialize";

	ovrHmdDesc desc = ovr_GetHmdDesc(nullptr);
	if (desc.Type == ovrHmd_None) {
		return false;
	}
	else {
		return true;
	}
}

bool OculusImpl::setup(const unsigned int color_texture_left, const unsigned int color_texture_right)
{
	// Make eye render buffers
	for (int eye = 0; eye < 2; eye++) {
		ovrSizei idealTextureSize;
		idealTextureSize.w = this->m_width[eye];
		idealTextureSize.h = this->m_height[eye];

		this->m_eyeRenderTexture[eye] = new TextureBuffer(this->m_hmd, idealTextureSize, 1);

		if (!this->m_eyeRenderTexture[eye]->TextureSet) {
			return false;
		}
	}

	ovrSizei bufferSize;
	bufferSize.w = this->m_width[0] + this->m_width[1];
	bufferSize.h = MAX(this->m_height[0], this->m_height[1]);

	ovrLayerEyeFov layer;
	layer.Header.Type = ovrLayerType_EyeFov;
	layer.Header.Flags = ovrLayerFlag_TextureOriginAtBottomLeft;   // Because OpenGL.

	for (int eye = 0; eye < 2; eye++) {
		layer.ColorTexture[eye] = this->m_eyeRenderTexture[eye]->TextureSet;
		layer.Viewport[eye] = Recti(this->m_eyeRenderTexture[eye]->GetSize());
		layer.Fov[eye] = this->m_eyeRenderDesc[eye].Fov;
	}
	// layer.RenderPose is updated later per frame

	/* store data */
	this->m_color_texture[0] = color_texture_left;
	this->m_color_texture[1] = color_texture_right;
	this->m_layer = layer;

	// Configure the read buffer
	for (int eye = 0; eye < 2; eye++) {
		glGenFramebuffers(1, &this->m_fbo[eye]);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, this->m_fbo[eye]);
		glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_color_texture[eye], 0);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	}

	// Turn off vsync to let the compositor do its magic
	wglSwapIntervalEXT(0);

	std::cout << "Oculus properly setup." << std::endl;
	return true;
};

static void formatMatrix(ovrMatrix4f matrix, float *r_matrix)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			r_matrix[i * 4 + j] = matrix.M[j][i];
}

bool OculusImpl::update(float *r_orientation_left, float *r_position_left, float *r_orientation_right, float *r_position_right)
{
	/* Get both eye poses simultaneously, with IPD offset already included */
	ovrFrameTiming ftiming = ovr_GetFrameTiming(this->m_hmd, ++this->m_frame);
	ovrTrackingState hmdState = ovr_GetTrackingState(this->m_hmd, ftiming.DisplayMidpointSeconds);

	if ((hmdState.StatusFlags & (ovrStatus_OrientationTracked | ovrStatus_PositionTracked)) != 0) {
		ovr_CalcEyePoses(hmdState.HeadPose.ThePose, this->m_hmdToEyeViewOffset, this->m_layer.RenderPose);

		float *orientation[2] = { r_orientation_left, r_orientation_right };
		float *position[2] = { r_position_left, r_position_right };

		for (int eye = 0; eye < 2; eye++) {
			orientation[eye][0] = this->m_layer.RenderPose[eye].Orientation.w;
			orientation[eye][1] = this->m_layer.RenderPose[eye].Orientation.x;
			orientation[eye][2] = this->m_layer.RenderPose[eye].Orientation.y;
			orientation[eye][3] = this->m_layer.RenderPose[eye].Orientation.z;

			position[eye][0] = this->m_scale * this->m_layer.RenderPose[eye].Position.x;
			position[eye][1] = this->m_scale * this->m_layer.RenderPose[eye].Position.y;
			position[eye][2] = this->m_scale * this->m_layer.RenderPose[eye].Position.z;
		}

		return true;
	}
	return false;
};

bool OculusImpl::update(
	float *r_yaw_left, float *r_pitch_left, float *r_roll_left, float *r_position_left,
	float *r_yaw_right, float *r_pitch_right, float *r_roll_right, float *r_position_right)
{
	/* Get both eye poses simultaneously, with IPD offset already included */
	ovrFrameTiming ftiming = ovr_GetFrameTiming(this->m_hmd, ++this->m_frame);
	ovrTrackingState hmdState = ovr_GetTrackingState(this->m_hmd, ftiming.DisplayMidpointSeconds);

	if ((hmdState.StatusFlags & (ovrStatus_OrientationTracked | ovrStatus_PositionTracked)) != 0) {
		ovr_CalcEyePoses(hmdState.HeadPose.ThePose, this->m_hmdToEyeViewOffset, this->m_layer.RenderPose);

		Quatf quat;

		quat = this->m_layer.RenderPose[0].Orientation;
		quat.GetYawPitchRoll(r_yaw_left, r_pitch_left, r_roll_left);

		quat = this->m_layer.RenderPose[1].Orientation;
		quat.GetYawPitchRoll(r_yaw_right, r_pitch_right, r_roll_right);

		r_position_left[0] = this->m_scale * this->m_layer.RenderPose[0].Position.x;
		r_position_left[1] = this->m_scale * this->m_layer.RenderPose[0].Position.y;
		r_position_left[2] = this->m_scale * this->m_layer.RenderPose[0].Position.z;

		r_position_right[0] = this->m_scale * this->m_layer.RenderPose[1].Position.x;
		r_position_right[1] = this->m_scale * this->m_layer.RenderPose[1].Position.y;
		r_position_right[2] = this->m_scale * this->m_layer.RenderPose[1].Position.z;
		return true;
	}
	return false;
};

bool OculusImpl::update(
	float *r_yaw_left, float *r_pitch_left, float *r_roll_left, float *r_orientation_left, float *r_position_left,
	float *r_yaw_right, float *r_pitch_right, float *r_roll_right, float *r_orientation_right, float *r_position_right)
{
	/* Get both eye poses simultaneously, with IPD offset already included */
	ovrFrameTiming ftiming = ovr_GetFrameTiming(this->m_hmd, ++this->m_frame);
	ovrTrackingState hmdState = ovr_GetTrackingState(this->m_hmd, ftiming.DisplayMidpointSeconds);

	if ((hmdState.StatusFlags & (ovrStatus_OrientationTracked | ovrStatus_PositionTracked)) != 0) {
		ovr_CalcEyePoses(hmdState.HeadPose.ThePose, this->m_hmdToEyeViewOffset, this->m_layer.RenderPose);

		Quatf quat;

		quat = this->m_layer.RenderPose[0].Orientation;
		quat.GetYawPitchRoll(r_yaw_left, r_pitch_left, r_roll_left);
		r_orientation_left[0] = quat.w;
		r_orientation_left[1] = quat.x;
		r_orientation_left[2] = quat.y;
		r_orientation_left[3] = quat.z;

		quat = this->m_layer.RenderPose[1].Orientation;
		quat.GetYawPitchRoll(r_yaw_right, r_pitch_right, r_roll_right);
		r_orientation_right[0] = quat.w;
		r_orientation_right[1] = quat.x;
		r_orientation_right[2] = quat.y;
		r_orientation_right[3] = quat.z;

		r_position_left[0] = this->m_scale * this->m_layer.RenderPose[0].Position.x;
		r_position_left[1] = this->m_scale * this->m_layer.RenderPose[0].Position.y;
		r_position_left[2] = this->m_scale * this->m_layer.RenderPose[0].Position.z;

		r_position_right[0] = this->m_scale * this->m_layer.RenderPose[1].Position.x;
		r_position_right[1] = this->m_scale * this->m_layer.RenderPose[1].Position.y;
		r_position_right[2] = this->m_scale * this->m_layer.RenderPose[1].Position.z;
		return true;
	}
	return false;
}

bool OculusImpl::update(float *r_matrix_left, float *r_matrix_right)
{
	/* Get both eye poses simultaneously, with IPD offset already included */
	ovrFrameTiming ftiming = ovr_GetFrameTiming(this->m_hmd, ++this->m_frame);
	ovrTrackingState hmdState = ovr_GetTrackingState(this->m_hmd, ftiming.DisplayMidpointSeconds);

	if ((hmdState.StatusFlags & (ovrStatus_OrientationTracked | ovrStatus_PositionTracked)) != 0) {
		ovr_CalcEyePoses(hmdState.HeadPose.ThePose, this->m_hmdToEyeViewOffset, this->m_layer.RenderPose);

		float *matrix[2] = { r_matrix_left, r_matrix_right };

		for (int eye = 0; eye < 2; eye++) {
			Vector3f pos = this->m_layer.RenderPose[eye].Position;
			Matrix4f rot = Matrix4f(this->m_layer.RenderPose[eye].Orientation);

			Vector3f finalUp = rot.Transform(Vector3f(0, 1, 0));
			Vector3f finalForward = rot.Transform(Vector3f(0, 0, -1));
			Matrix4f view = Matrix4f::LookAtRH(pos, pos + finalForward, finalUp);

			formatMatrix(view, matrix[eye]);
		}
		return true;
	}
	return false;
}

bool OculusImpl::frameReady()
{
	for (int eye = 0; eye < 2; eye++) {
		// Increment to use next texture, just before writing
		this->m_eyeRenderTexture[eye]->TextureSet->CurrentIndex = (this->m_eyeRenderTexture[eye]->TextureSet->CurrentIndex + 1) % this->m_eyeRenderTexture[eye]->TextureSet->TextureCount;

		// Switch to eye render target
		this->m_eyeRenderTexture[eye]->SetAndClearRenderSurface();

		GLint w = this->m_eyeRenderTexture[eye]->texSize.w;
		GLint h = this->m_eyeRenderTexture[eye]->texSize.h;

		// copy result from color_texture to HMD
		glBindFramebuffer(GL_READ_FRAMEBUFFER, this->m_fbo[eye]);
		glBlitFramebuffer(0, 0, w, h,
		                  0, 0, w, h,
		                  GL_COLOR_BUFFER_BIT, GL_NEAREST);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

		this->m_eyeRenderTexture[eye]->UnsetRenderSurface();
	}

	ovrLayerHeader *layers = &this->m_layer.Header;
	ovrResult result = ovr_SubmitFrame(this->m_hmd, this->m_frame, nullptr, &layers, 1);

	if (ovrSuccess != result)
		return false;

	return true;
};

bool OculusImpl::reCenter()
{
	ovr_RecenterPose(this->m_hmd);
	return true;
};

void OculusImpl::getProjectionMatrixLeft(const float nearz, const float farz, const bool is_opengl, const bool is_right_hand, float *r_matrix)
{
	unsigned int flags = getProjectionMatrixFlags(is_opengl, is_right_hand);

	ovrMatrix4f matrix = ovrMatrix4f_Projection(
		this->m_eyeRenderDesc[0].Fov,
		nearz,
		farz,
		flags);

	formatMatrix(matrix, r_matrix);
}

void OculusImpl::getProjectionMatrixRight(const float nearz, const float farz, const bool is_opengl, const bool is_right_hand, float *r_matrix)
{
	unsigned int flags = getProjectionMatrixFlags(is_opengl, is_right_hand);

	ovrMatrix4f matrix = ovrMatrix4f_Projection(
		this->m_eyeRenderDesc[1].Fov,
		nearz,
		farz,
		flags);

	formatMatrix(matrix, r_matrix);
}

unsigned int OculusImpl::getProjectionMatrixFlags(const bool is_opengl, const bool is_right_hand)
{
	unsigned int flags = is_right_hand ? ovrProjection_RightHanded : ovrProjection_None;

	if (is_opengl) {
		flags |= ovrProjection_ClipRangeOpenGL;
	}
	return flags;
}


Oculus::Oculus() 
	: Backend()
	, m_me(new OculusImpl)
{	
}

Oculus::~Oculus()
{
	if (this->m_me) {
		delete this->m_me;
	}
}

bool Oculus::setup(const unsigned int color_texture_left, const unsigned int color_texture_right)
{
	return this->m_me->setup(color_texture_left, color_texture_right);
}

bool Oculus::update(float *r_orientation_left, float *r_position_left, float *r_orientation_right, float *r_position_right)
{
	return this->m_me->update(r_orientation_left, r_position_left, r_orientation_right, r_position_right);
}

bool Oculus::update(
	float *r_yaw_left, float *r_pitch_left, float *r_roll_left, float *r_position_left,
	float *r_yaw_right, float *r_pitch_right, float *r_roll_right, float *r_position_right)
{
	return this->m_me->update(
		r_yaw_left, r_pitch_left, r_roll_left, r_position_left,
		r_yaw_right, r_pitch_right, r_roll_right, r_position_right);
}

bool Oculus::update(
	float *r_yaw_left, float *r_pitch_left, float *r_roll_left, float *r_orientation_left, float *r_position_left,
	float *r_yaw_right, float *r_pitch_right, float *r_roll_right, float *r_orientation_right, float *r_position_right)
{
	return this->m_me->update(
		r_yaw_left, r_pitch_left, r_roll_left, r_orientation_left, r_position_left,
		r_yaw_right, r_pitch_right, r_roll_right, r_orientation_right, r_position_right);
}

bool Oculus::update(float *r_matrix_left, float *r_matrix_right)
{
	return this->m_me->update(r_matrix_left, r_matrix_right);
}

bool Oculus::frameReady()
{
	return this->m_me->frameReady();
}

bool Oculus::reCenter()
{
	return this->m_me->reCenter();
}

void Oculus::getProjectionMatrixLeft(const float nearz, const float farz, const bool is_opengl, const bool is_right_hand, float *r_matrix)
{
	return this->m_me->getProjectionMatrixLeft(nearz, farz, is_opengl, is_right_hand, r_matrix);
}

void Oculus::getProjectionMatrixRight(const float nearz, const float farz, const bool is_opengl, const bool is_right_hand, float *r_matrix)
{
	return this->m_me->getProjectionMatrixRight(nearz, farz, is_opengl, is_right_hand, r_matrix);
}

int Oculus::getWidthLeft()
{
	return this->m_me->getWidthLeft();
}

int Oculus::getWidthRight()
{
	return this->m_me->getWidthRight();
}

int Oculus::getHeightLeft()
{
	return this->m_me->getHeightLeft();
}

int Oculus::getHeightRight()
{
	return this->m_me->getHeightRight();
}

float Oculus::getScale()
{
	return this->m_me->getScale();
}

void Oculus::setScale(const float scale)
{
	this->m_me->setScale(scale);
}