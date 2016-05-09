#ifndef MATH_QUATERNIONS_H
#define MATH_QUATERNIONS_H

//========= @cedeon (William Culver)'s Flaky Mathematics Helper. ===========
//
// Description: I piece-mealed some code on the internets.  Warning, i have
// a dangerously un-Grok'd comprehension of this math.
//
//=============================================================================
#include "Vectors.h"
#include "Matrices.h"
#include <math.h>       /* sqrt */

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
	static void GetPosition(Vector3 &v, const Matrix4 &matrix);
	static void GetScale(Vector3 &v, const Matrix4 &matrix);
};

/*
*  Modifies param: q
*/
inline void MatrixHelper::GetRotation(Quaternion &q, const Matrix4 &matrix)
{
	q.w = sqrt(fmax(0, 1 + matrix.get()[0] + matrix.get()[5] + matrix.get()[10])) / 2;
	q.x = sqrt(fmax(0, 1 + matrix.get()[0] - matrix.get()[5] - matrix.get()[10])) / 2;
	q.y = sqrt(fmax(0, 1 - matrix.get()[0] + matrix.get()[5] - matrix.get()[10])) / 2;
	q.z = sqrt(fmax(0, 1 - matrix.get()[0] - matrix.get()[5] + matrix.get()[10])) / 2;
	q.x = _copysign(q.x, matrix.get()[9] - matrix.get()[6]);
	q.y = _copysign(q.y, matrix.get()[2] - matrix.get()[8]);
	q.z = _copysign(q.z, matrix.get()[4] - matrix.get()[1]);
}

inline void MatrixHelper::GetPosition(Vector3 &v, const Matrix4 &matrix)
{
	v.x = matrix.get()[3];
	v.y = matrix.get()[7];
	v.z = matrix.get()[11];
}

inline void MatrixHelper::GetScale(Vector3 &v, const Matrix4 &matrix)
{
	v.x = sqrt(matrix.get()[0] * matrix.get()[0] + matrix.get()[1] * matrix.get()[1] + matrix.get()[2] * matrix.get()[2]);
	v.y = sqrt(matrix.get()[4] * matrix.get()[4] + matrix.get()[5] * matrix.get()[5] + matrix.get()[6] * matrix.get()[6]);
	v.z = sqrt(matrix.get()[8] * matrix.get()[8] + matrix.get()[9] * matrix.get()[9] + matrix.get()[10] * matrix.get()[10]);
}

#endif