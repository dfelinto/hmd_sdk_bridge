#ifndef __OCULUS_H__
#define __OCULUS_H__

#include "GL/glew.h"
#include "GL/wglew.h"

#include "HMD.h"
#include "OVR_CAPI_0_7_0.h"
#include "OVR_CAPI_GL.h"

#include <Extras/OVR_Math.h>
#include <Kernel/OVR_Log.h>

using namespace OVR;

typedef enum eLibStatus
{
	LIB_UNLOADED = 0,
	LIB_FAILED,
	LIB_INITIALIZED,
};


/* TextureBuffer copied/adapted from Oculus SDK samples */
struct TextureBuffer
{
	ovrHmd              hmd;
	ovrSwapTextureSet*  TextureSet;
	GLuint              fboId;
	Sizei               texSize;

	TextureBuffer(ovrHmd hmd, Sizei size, int sampleCount):
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

class Oculus : public HMD
{
public:
	Oculus();
	~Oculus();

	bool setup(const unsigned int color_texture_left, const unsigned int color_texture_right);

	bool update(float *r_orientation_left, float *r_position_left, float *r_orientation_right, float *r_position_right);

	bool frameReady(void);

	bool reCenter(void);

	void getProjectionMatrixLeft(const float nearz, const float farz, float *r_matrix);

	void getProjectionMatrixRight(const float nearz, const float farz, float *r_matrix);

	static bool initializeLibrary(void);

private:
	bool isConnected(void);
	unsigned int m_frame;
	ovrHmd m_hmd;
	ovrHmdDesc m_desc;
	ovrLayerEyeFov m_layer;

	ovrEyeRenderDesc m_eyeRenderDesc[2];
	ovrVector3f m_hmdToEyeViewOffset[2];
	TextureBuffer *m_eyeRenderTexture[2];
	static eLibStatus m_lib_status;

	GLuint m_fbo[2];
};

#endif /* __OCULUS_H__ */