#ifndef __BRIDGE_C_API_H__
#define __BRIDGE_C_API_H__

#include "HMD.h"
#include "Oculus.h"

#if defined(_WIN32)
#define EXPORT_LIB extern "C" __declspec(dllexport)
#else
#define EXPORT_LIB extern "C"
#endif

EXPORT_LIB int functionTest(int input);

/* Oculus wrapper */
EXPORT_LIB Oculus *Oculus_new(){ return new Oculus(); }
EXPORT_LIB bool Oculus_isConnected(){ return Oculus::isConnected(); }
EXPORT_LIB bool Oculus_setup(Oculus *oculus, const unsigned int framebuffer_object_left, const unsigned int framebuffer_object_right){ return oculus->setup(framebuffer_object_left, framebuffer_object_right); }
EXPORT_LIB bool Oculus_update(Oculus *oculus, float *r_head_transform[4][4], float *r_eye_left[3], float *r_eye_right[3]) { return oculus->update(r_head_transform, r_eye_left, r_eye_right); }
EXPORT_LIB bool Oculus_frameReady(Oculus *oculus) { return oculus->frameReady(); }
EXPORT_LIB bool Oculus_reCenter(Oculus *oculus) { return oculus->reCenter(); }
EXPORT_LIB unsigned int Oculus_width(Oculus *oculus) { return oculus->getWidth(); }
EXPORT_LIB unsigned int Oculus_height(Oculus *oculus) { return oculus->getHeight(); }
EXPORT_LIB void Oculus_projectionMatrixLeft(Oculus *oculus, const float nearz, const float farz, float *r_matrix[4][4]) { return oculus->getProjectionMatrixLeft(nearz, farz, r_matrix); }
EXPORT_LIB void Oculus_projectionMatrixRight(Oculus *oculus, const float nearz, const float farz, float *r_matrix[4][4]) { return oculus->getProjectionMatrixRight(nearz, farz, r_matrix); }

#endif /* __BRIDGE_C_API_H__ */