#ifndef __BRIDGE_C_API_H__
#define __BRIDGE_C_API_H__

#include "Debug.h"

#include "HMD.h"

#if defined(_WIN32) || defined(_WIN64)
#if defined DLL_EXPORT
#define EXPORT_LIB extern "C" __declspec(dllexport)
#else
#define EXPORT_LIB extern "C" __declspec(dllimport)
#endif
#else
#define EXPORT_LIB extern "C"
#endif

/* Debug wrapper */
EXPORT_LIB Debug *Debug_new(int number) { return new Debug(number); }
EXPORT_LIB void Debug_del(Debug *debug) { if (debug) { delete debug; debug = NULL; } }
EXPORT_LIB int Debug_multiplicationFactor() { return Debug::multiplicationFactor(); }
EXPORT_LIB int Debug_multiplicationResult(Debug *debug) { return debug->multiplicationResult(); }
EXPORT_LIB void Debug_matrix(float *r_float) { Debug::matrix(r_float);}
EXPORT_LIB void Debug_matrixNonStatic(Debug *debug, float *r_float) { debug->matrixNonStatic(r_float); }
EXPORT_LIB void Debug_draw(const unsigned int color_texture) { Debug::draw(color_texture); }

EXPORT_LIB HMD *HMD_new(HMD::eHMDBackend backend){ return new HMD(backend); }
EXPORT_LIB void HMD_del(HMD *hmd){ if (hmd) delete hmd; }
EXPORT_LIB bool HMD_setup(HMD *hmd, const unsigned int color_texture_left, const unsigned int color_texture_right){ return hmd->setup(color_texture_left, color_texture_right); }
EXPORT_LIB bool HMD_update(HMD *hmd, float *r_orientation_left, float *r_position_left, float *r_orientation_right, float *r_position_right){ return hmd->update(r_orientation_left, r_position_left, r_orientation_right, r_position_right); };
EXPORT_LIB bool HMD_frameReady(HMD *hmd) { return hmd->frameReady(); }
EXPORT_LIB bool HMD_reCenter(HMD *hmd) { return hmd->reCenter(); }
EXPORT_LIB unsigned int HMD_widthLeft(HMD *hmd) { return hmd->getWidthLeft(); }
EXPORT_LIB unsigned int HMD_heightLeft(HMD *hmd) { return hmd->getHeightLeft(); }
EXPORT_LIB unsigned int HMD_widthRight(HMD *hmd) { return hmd->getWidthRight(); }
EXPORT_LIB unsigned int HMD_heightRight(HMD *hmd) { return hmd->getHeightRight(); }
EXPORT_LIB void HMD_projectionMatrixLeft(HMD *hmd, const float nearz, const float farz, float *r_matrix) { hmd->getProjectionMatrixLeft(nearz, farz, true, true, r_matrix); }
EXPORT_LIB void HMD_projectionMatrixRight(HMD *hmd, const float nearz, const float farz, float *r_matrix) { hmd->getProjectionMatrixRight(nearz, farz, true, true, r_matrix); }
EXPORT_LIB float HMD_scaleGet(HMD *hmd) { return hmd->getScale(); }
EXPORT_LIB void HMD_scaleSet(HMD *hmd, const float scale) { hmd->setScale(scale); }
EXPORT_LIB const char* HMD_getStatus(HMD *hmd) { return hmd->getStatus(); }
EXPORT_LIB bool HMD_getStateBool(HMD *hmd) { return hmd->getStateBool(); }

#ifdef OCULUS
/* Oculus wrapper - kept for backward compatibility */
EXPORT_LIB HMD *Oculus_new(){ return new HMD(HMD::eHMDBackend::BACKEND_OCULUS); }
EXPORT_LIB void Oculus_del(HMD *hmd){ if (hmd) delete hmd; }
EXPORT_LIB bool Oculus_setup(HMD *hmd, const unsigned int color_texture_left, const unsigned int color_texture_right){ return hmd->setup(color_texture_left, color_texture_right); }
EXPORT_LIB bool Oculus_update(HMD *hmd, float *r_orientation_left, float *r_position_left, float *r_orientation_right, float *r_position_right){ return hmd->update(r_orientation_left, r_position_left, r_orientation_right, r_position_right); };
EXPORT_LIB bool Oculus_frameReady(HMD *hmd) { return hmd->frameReady(); }
EXPORT_LIB bool Oculus_reCenter(HMD *hmd) { return hmd->reCenter(); }
EXPORT_LIB unsigned int Oculus_widthLeft(HMD *hmd) { return hmd->getWidthLeft(); }
EXPORT_LIB unsigned int Oculus_heightLeft(HMD *hmd) { return hmd->getHeightLeft(); }
EXPORT_LIB unsigned int Oculus_widthRight(HMD *hmd) { return hmd->getWidthRight(); }
EXPORT_LIB unsigned int Oculus_heightRight(HMD *hmd) { return hmd->getHeightRight(); }
EXPORT_LIB void Oculus_projectionMatrixLeft(HMD *hmd, const float nearz, const float farz, float *r_matrix) { hmd->getProjectionMatrixLeft(nearz, farz, true, true, r_matrix); }
EXPORT_LIB void Oculus_projectionMatrixRight(HMD *hmd, const float nearz, const float farz, float *r_matrix) { hmd->getProjectionMatrixRight(nearz, farz, true, true, r_matrix); }
EXPORT_LIB float Oculus_scaleGet(HMD *hmd) { return hmd->getScale(); }
EXPORT_LIB void Oculus_scaleSet(HMD *hmd, const float scale) { hmd->setScale(scale); }
EXPORT_LIB const char* Oculus_getStatus(HMD *hmd) { return hmd->getStatus(); }
EXPORT_LIB bool Oculus_getStateBool(HMD *hmd) { return hmd->getStateBool(); }
#endif

#undef EXPORT_LIB
#endif /* __BRIDGE_C_API_H__ */
