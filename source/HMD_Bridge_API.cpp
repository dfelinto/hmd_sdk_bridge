#include "HMD_Bridge_API.h"

#include "Backend.h"

#include "Stub.h"

#if defined OCULUS
#include "Oculus.h"
#endif

/* C++ API */

/* legacy overload constructor */
HMD::HMD():
	m_hmd(nullptr)
{
#if defined OCULUS
	m_hmd = new Oculus();
#else
	m_hmd = new Stub();
#endif
}

HMD::HMD(eHMDBackend backend):
	m_hmd(nullptr)
{
	switch (backend) {
		case BACKEND_OCULUS:
#if defined OCULUS
			m_hmd = new Oculus();
			break;
#endif
		case BACKEND_VIVE:
		default:
			m_hmd = new Stub();
			break;
	}
}

HMD::~HMD(void)
{
	if (m_hmd) {
		delete m_hmd;
	}
}

/* passthrough routines */

bool HMD::setup(const unsigned int color_texture_left, const unsigned int color_texture_right)
{
	return m_hmd->setup(color_texture_left, color_texture_right);
}

bool HMD::update(float *r_orientation_left, float *r_position_left, float *r_orientation_right, float *r_position_right)
{
	return m_hmd->update(r_orientation_left, r_position_left, r_orientation_right, r_position_right);
}

bool HMD::update(
	float *r_yaw_left, float *r_pitch_left, float *r_roll_left, float *r_position_left,
	float *r_yaw_right, float *r_pitch_right, float *r_roll_right, float *r_position_right)
{
	return m_hmd->update(
		r_yaw_left, r_pitch_left, r_roll_left, r_position_left,
		r_yaw_right, r_pitch_right, r_roll_right, r_position_right);
}

bool HMD::update(
	float *r_yaw_left, float *r_pitch_left, float *r_roll_left, float *r_orientation_left, float *r_position_left,
	float *r_yaw_right, float *r_pitch_right, float *r_roll_right, float *r_orientation_right, float *r_position_right)
{
	return m_hmd->update(
		r_yaw_left, r_pitch_left, r_roll_left, r_orientation_left, r_position_left,
		r_yaw_right, r_pitch_right, r_roll_right, r_orientation_right, r_position_right);
}

bool HMD::update(const bool is_right_hand, float *r_matrix_left, float *r_matrix_right)
{
	return m_hmd->update(is_right_hand, r_matrix_left, r_matrix_right);
}

bool HMD::frameReady(void)
{
	return m_hmd->frameReady();
}

bool HMD::reCenter(void)
{
	return m_hmd->reCenter();
}

void HMD::getProjectionMatrixLeft(const float nearz, const float farz, const bool is_opengl, const bool is_right_hand, float *r_matrix)
{
	return m_hmd->getProjectionMatrixLeft(nearz, farz, is_opengl, is_right_hand, r_matrix);
}

void HMD::getProjectionMatrixRight(const float nearz, const float farz, const bool is_opengl, const bool is_right_hand, float *r_matrix)
{
	return m_hmd->getProjectionMatrixRight(nearz, farz, is_opengl, is_right_hand, r_matrix);
}

int HMD::getWidthLeft()
{
	return m_hmd->getWidthLeft();
}

int HMD::getHeightLeft()
{
	return m_hmd->getHeightLeft();
}

int HMD::getWidthRight() {
	return m_hmd->getWidthRight();
}

int HMD::getHeightRight() {
	return m_hmd->getHeightRight();
}

float HMD::getScale() {
	return m_hmd->getScale();
}

void HMD::setScale(const float scale) {
	m_hmd->setScale(scale);
}

/* C API */

HMD *HMD_new(HMD::eHMDBackend backend)
{
	return new HMD(backend);
}

void HMD_del(HMD *hmd)
{
	if (hmd) delete hmd;
}

bool HMD_setup(HMD *hmd, const unsigned int color_texture_left, const unsigned int color_texture_right)
{
	return hmd->setup(color_texture_left, color_texture_right);
}

bool HMD_update(HMD *hmd, float *r_orientation_left, float *r_position_left, float *r_orientation_right, float *r_position_right)
{
	return hmd->update(r_orientation_left, r_position_left, r_orientation_right, r_position_right);
};

bool HMD_frameReady(HMD *hmd)
{
	return hmd->frameReady();
}

bool HMD_reCenter(HMD *hmd)
{
	return hmd->reCenter();
}

unsigned int HMD_widthLeft(HMD *hmd)
{
	return hmd->getWidthLeft();
}

unsigned int HMD_heightLeft(HMD *hmd)
{
	return hmd->getHeightLeft();
}

unsigned int HMD_widthRight(HMD *hmd)
{
	return hmd->getWidthRight();
}

unsigned int HMD_heightRight(HMD *hmd)
{
	return hmd->getHeightRight();
}

void HMD_projectionMatrixLeft(HMD *hmd, const float nearz, const float farz, float *r_matrix)
{
	hmd->getProjectionMatrixLeft(nearz, farz, true, true, r_matrix);
}

void HMD_projectionMatrixRight(HMD *hmd, const float nearz, const float farz, float *r_matrix)
{
	hmd->getProjectionMatrixRight(nearz, farz, true, true, r_matrix);
}

float HMD_scaleGet(HMD *hmd)
{
	return hmd->getScale();
}

void HMD_scaleSet(HMD *hmd, const float scale)
{
	hmd->setScale(scale);
}

/* Legacy C API */

#include <iostream>
/* Oculus wrapper - kept for backward compatibility */
HMD *Oculus_new()
{
	std::cout << "HMD SDK Bridge Legacy API is deprecated, please contact your software developer." << std::endl;
	return new HMD(HMD::eHMDBackend::BACKEND_OCULUS);
}

void Oculus_del(HMD *hmd)
{
	if (hmd) delete hmd;
}

bool Oculus_setup(HMD *hmd, const unsigned int color_texture_left, const unsigned int color_texture_right)
{
	return hmd->setup(color_texture_left, color_texture_right);
}

bool Oculus_update(HMD *hmd, float *r_orientation_left, float *r_position_left, float *r_orientation_right, float *r_position_right)
{
	return hmd->update(r_orientation_left, r_position_left, r_orientation_right, r_position_right);
}

bool Oculus_frameReady(HMD *hmd)
{
	return hmd->frameReady();
}

bool Oculus_reCenter(HMD *hmd)
{
	return hmd->reCenter();
}

unsigned int Oculus_widthLeft(HMD *hmd)
{
	return hmd->getWidthLeft();
}

unsigned int Oculus_heightLeft(HMD *hmd)
{
	return hmd->getHeightLeft();
}

unsigned int Oculus_widthRight(HMD *hmd)
{
	return hmd->getWidthRight();
}

unsigned int Oculus_heightRight(HMD *hmd)
{
	return hmd->getHeightRight();
}

void Oculus_projectionMatrixLeft(HMD *hmd, const float nearz, const float farz, float *r_matrix)
{
	hmd->getProjectionMatrixLeft(nearz, farz, true, true, r_matrix);
}

void Oculus_projectionMatrixRight(HMD *hmd, const float nearz, const float farz, float *r_matrix)
{
	hmd->getProjectionMatrixRight(nearz, farz, true, true, r_matrix);
}

float Oculus_scaleGet(HMD *hmd)
{
	return hmd->getScale();
}

void Oculus_scaleSet(HMD *hmd, const float scale)
{
	hmd->setScale(scale);
}