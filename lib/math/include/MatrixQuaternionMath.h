#ifndef MATH_QUATERNIONS_H
#define MATH_QUATERNIONS_H

//===== @cedeon (William Culver)'s Matrix / Quaternion Helper Functions. =====
//
// Description: I piece-mealed some code from the internets.  Warning, i have
// a dangerously un-Grok'd comprehension of this math. NO WARRANTY
//
//=============================================================================
#include "Vectors.h"
#include "Matrices.h"
#include <math.h> 

class Quaternion
{
public:
	float w, x, y, z;
	Quaternion();
	~Quaternion();
private:
};

Quaternion::Quaternion() 
	:w(0), x(0), y(0), z(0)
{

}

Quaternion::~Quaternion()
{

}


class MatrixHelper
{
public:
	MatrixHelper();
	~MatrixHelper();
	static void GetRotation(Quaternion &q, const Matrix4 &matrix);
	static void CalculateRotation(Quaternion& q, const Matrix4 &matrix);
	static void GetPosition(Vector3 &v, const Matrix4 &matrix);
	static void GetScale(Vector3 &v, const Matrix4 &matrix);
};

/*
*  GetRotation : Doesn't Work!  Use CalculateRotation instead.  TODO: Fix
*/
inline void MatrixHelper::GetRotation(Quaternion &q, const Matrix4 &matrix)
{
	q.w = (float)sqrt(fmax(0, 1 + matrix.get()[0] + matrix.get()[5] + matrix.get()[10])) / 2;
	q.x = (float)sqrt(fmax(0, 1 + matrix.get()[0] - matrix.get()[5] - matrix.get()[10])) / 2;
	q.y = (float)sqrt(fmax(0, 1 - matrix.get()[0] + matrix.get()[5] - matrix.get()[10])) / 2;
	q.z = (float)sqrt(fmax(0, 1 - matrix.get()[0] - matrix.get()[5] + matrix.get()[10])) / 2;
	q.x = (float)_copysign(q.x, matrix.get()[6] - matrix.get()[9]);
	q.y = (float)_copysign(q.y, matrix.get()[8] - matrix.get()[2]);
	q.z = (float)_copysign(q.z, matrix.get()[1] - matrix.get()[4]);
}

inline void MatrixHelper::CalculateRotation(Quaternion& q, const Matrix4 &matrix)  
{
	float trace = matrix.get()[0] + matrix.get()[5] + matrix.get()[10]; // I removed + 1.0f; see discussion with Ethan
	if (trace > 0) {// I changed M_EPSILON to 0
		float s = 0.5f / sqrtf(trace + 1.0f);
		q.w = 0.25f / s;
		q.x = (matrix.get()[6] - matrix.get()[9]) * s;
		q.y = (matrix.get()[8] - matrix.get()[2]) * s;
		q.z = (matrix.get()[1] - matrix.get()[4]) * s;
	}
	else {
		if (matrix.get()[0] > matrix.get()[5] && matrix.get()[0] > matrix.get()[10]) {
			float s = 2.0f * sqrtf(1.0f + matrix.get()[0] - matrix.get()[5] - matrix.get()[10]);
			q.w = (matrix.get()[6] - matrix.get()[9]) / s;
			q.x = 0.25f * s;
			q.y = (matrix.get()[4] + matrix.get()[1]) / s;
			q.z = (matrix.get()[8] + matrix.get()[2]) / s;
		}
		else if (matrix.get()[5] > matrix.get()[10]) {
			float s = 2.0f * sqrtf(1.0f + matrix.get()[5] - matrix.get()[0] - matrix.get()[10]);
			q.w = (matrix.get()[8] - matrix.get()[2]) / s;
			q.x = (matrix.get()[4] + matrix.get()[1]) / s;
			q.y = 0.25f * s;
			q.z = (matrix.get()[9] + matrix.get()[6]) / s;
		}
		else {
			float s = 2.0f * sqrtf(1.0f + matrix.get()[10] - matrix.get()[0] - matrix.get()[5]);
			q.w = (matrix.get()[1] - matrix.get()[4]) / s;
			q.x = (matrix.get()[8] + matrix.get()[2]) / s;
			q.y = (matrix.get()[9] + matrix.get()[6]) / s;
			q.z = 0.25f * s;
		}
	}
}

inline void MatrixHelper::GetPosition(Vector3 &v, const Matrix4 &matrix)
{
	v.x = matrix.get()[12];
	v.y = matrix.get()[13];
	v.z = matrix.get()[14];
}

inline void MatrixHelper::GetScale(Vector3 &v, const Matrix4 &matrix)
{
	v.x = sqrt(matrix.get()[0] * matrix.get()[0] + matrix.get()[4] * matrix.get()[4] + matrix.get()[8] * matrix.get()[8]);
	v.y = sqrt(matrix.get()[1] * matrix.get()[1] + matrix.get()[5] * matrix.get()[5] + matrix.get()[9] * matrix.get()[9]);
	v.z = sqrt(matrix.get()[2] * matrix.get()[2] + matrix.get()[6] * matrix.get()[6] + matrix.get()[10] * matrix.get()[10]);
}

#endif