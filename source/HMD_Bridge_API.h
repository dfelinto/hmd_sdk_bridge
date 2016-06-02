#ifndef __HMD_BRIDGE_API_H__
#define __HMD_BRIDGE_API_H__


/* C API */
#if defined(_WIN32) || defined(_WIN64)
#ifdef __cplusplus
#define EXPORT_LIB extern "C" __declspec(dllimport)
#else
#define EXPORT_LIB __declspec(dllimport)
#endif
#else
#ifdef __cplusplus
#define EXPORT_LIB extern "C"
#else
#define EXPORT_LIB
#endif
#endif

#ifdef __cplusplus

/* C++ API */
#if defined(_WIN32) || defined(_WIN64)
#if !defined(DllExport)
	#define DllExport   __declspec( dllexport )  
#endif

#else
#define DllExport
#endif


/* Forward declarations */
class Backend;

/* Interface */
class DllExport HMD
{
public:

  enum eHMDBackend
	{
		BACKEND_OCULUS = 0,
		BACKEND_OCULUS_LEGACY,
		BACKEND_VIVE,
		BACKEND_OSVR,
		BACKEND_OPENVR,
		BACKEND_OPENHMD,
	};

	HMD();

	HMD(eHMDBackend backend);

	~HMD(void);

	bool setup(const unsigned int color_texture_left, const unsigned int color_texture_right);

	bool update(float *r_orientation_left, float *r_position_left, float *r_orientation_right, float *r_position_right);

	bool update(
		float *r_yaw_left, float *r_pitch_left, float *r_roll_left, float *r_position_left,
		float *r_yaw_right, float *r_pitch_right, float *r_roll_right, float *r_position_right);

	bool update(
		float *r_yaw_left, float *r_pitch_left, float *r_roll_left, float *r_orientation_left, float *r_position_left,
		float *r_yaw_right, float *r_pitch_right, float *r_roll_right, float *r_orientation_right, float *r_position_right);

	bool update(const bool is_right_hand, float *r_matrix_left, float *r_matrix_right);

	bool frameReady(void);

	bool reCenter(void);

	void getProjectionMatrixLeft(const float nearz, const float farz, const bool is_opengl, const bool is_right_hand, float *r_matrix);

	void getProjectionMatrixRight(const float nearz, const float farz, const bool is_opengl, const bool is_right_hand, float *r_matrix);

	/* generic */
	int getWidthLeft();
	int getHeightLeft();
	int getWidthRight();
	int getHeightRight();
	float getScale();
	void setScale(const float scale);

protected:
	Backend *m_hmd;
};

#endif /* __cplusplus */


/* C API */

/* Debug wrapper */
#ifdef DEBUG_BRIDGE
EXPORT_LIB Debug *Debug_new(int number) { return new Debug(number); }
EXPORT_LIB void Debug_del(Debug *debug) { if (debug) { delete debug; debug = NULL; } }
EXPORT_LIB int Debug_multiplicationFactor() { return Debug::multiplicationFactor(); }
EXPORT_LIB int Debug_multiplicationResult(Debug *debug) { return debug->multiplicationResult(); }
EXPORT_LIB void Debug_matrix(float *r_float) { Debug::matrix(r_float);}
EXPORT_LIB void Debug_matrixNonStatic(Debug *debug, float *r_float) { debug->matrixNonStatic(r_float); }
EXPORT_LIB void Debug_draw(const unsigned int color_texture) { Debug::draw(color_texture); }
#endif

EXPORT_LIB HMD *HMD_new(HMD::eHMDBackend backend);
EXPORT_LIB void HMD_del(HMD *hmd);
EXPORT_LIB bool HMD_setup(HMD *hmd, const unsigned int color_texture_left, const unsigned int color_texture_right);
EXPORT_LIB bool HMD_update(HMD *hmd, float *r_orientation_left, float *r_position_left, float *r_orientation_right, float *r_position_right);
EXPORT_LIB bool HMD_frameReady(HMD *hmd);
EXPORT_LIB bool HMD_reCenter(HMD *hmd);
EXPORT_LIB unsigned int HMD_widthLeft(HMD *hmd);
EXPORT_LIB unsigned int HMD_heightLeft(HMD *hmd);
EXPORT_LIB unsigned int HMD_widthRight(HMD *hmd);
EXPORT_LIB unsigned int HMD_heightRight(HMD *hmd);
EXPORT_LIB void HMD_projectionMatrixLeft(HMD *hmd, const float nearz, const float farz, float *r_matrix);
EXPORT_LIB void HMD_projectionMatrixRight(HMD *hmd, const float nearz, const float farz, float *r_matrix);
EXPORT_LIB float HMD_scaleGet(HMD *hmd);
EXPORT_LIB void HMD_scaleSet(HMD *hmd, const float scale);

#ifdef OCULUS
/* Oculus wrapper - kept for backward compatibility */
EXPORT_LIB HMD *Oculus_new();
EXPORT_LIB void Oculus_del(HMD *hmd);
EXPORT_LIB bool Oculus_setup(HMD *hmd, const unsigned int color_texture_left, const unsigned int color_texture_right);
EXPORT_LIB bool Oculus_update(HMD *hmd, float *r_orientation_left, float *r_position_left, float *r_orientation_right, float *r_position_right);
EXPORT_LIB bool Oculus_frameReady(HMD *hmd);
EXPORT_LIB bool Oculus_reCenter(HMD *hmd);
EXPORT_LIB unsigned int Oculus_widthLeft(HMD *hmd);
EXPORT_LIB unsigned int Oculus_heightLeft(HMD *hmd);
EXPORT_LIB unsigned int Oculus_widthRight(HMD *hmd);
EXPORT_LIB unsigned int Oculus_heightRight(HMD *hmd);
EXPORT_LIB void Oculus_projectionMatrixLeft(HMD *hmd, const float nearz, const float farz, float *r_matrix);
EXPORT_LIB void Oculus_projectionMatrixRight(HMD *hmd, const float nearz, const float farz, float *r_matrix);
EXPORT_LIB float Oculus_scaleGet(HMD *hmd);
EXPORT_LIB void Oculus_scaleSet(HMD *hmd, const float scale);
#endif

#undef EXPORT_LIB

#endif /* __HMD_BRIDGE_API_H__ */
