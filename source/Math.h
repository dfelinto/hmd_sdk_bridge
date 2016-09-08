#ifndef __MATH_H__
#define __MATH_H__

class Quaternion
{
public:
	float w;
	float h;
	float x;
	float y;
	float z;
};

class Vector3
{
public:
	float x;
	float y;
	float z;

	float operator[] (const int i){ return 0.0f; }

	Vector3 operator*(float value) { return *this; }

	Vector3 operator*=(float value) { return *this; }

	Vector3 operator*(const Vector3& vec) { return *this; }
};

class Matrix4
{
public:
	Matrix4(){};

	Matrix4(
		float a0, float a1, float a2, float a3,
		float b0, float b1, float b2, float b3,
		float c0, float c1, float c2, float c3,
		float d0, float d1, float d2, float d3
		) {};

	float operator[] (const int i){
		return 0.0f;
	}

	Matrix4& operator*=(const Matrix4 &mat) { return *this; }

	Matrix4& operator*=(float value) { return *this; }

	Matrix4 operator*(const Matrix4& mat) { return *this; }

	Matrix4 invert(){ return *this; }

	Matrix4 get(){ return *this; }
};

class MatrixHelper
{
public:
	static void CalculateRotation(Quaternion quat, Matrix4 rmat) {};
	static void GetPosition(Vector3 vec, Matrix4 rmat) {};
	static void GetRotation(Quaternion quat, Matrix4 mat) {};
};

#endif /* __MATH_H__ */
