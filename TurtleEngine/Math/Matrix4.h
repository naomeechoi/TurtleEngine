#pragma once
#include "Vector3.h"

class alignas(16) Matrix4
{
public:
	Matrix4();
	Matrix4(const Matrix4& other);
	~Matrix4();

	static uint32 ByteWidth() { return sizeof(float) * elementSize; }

	static Matrix4 Identity();
	static Matrix4 Translation(const Vector3& position);
	static Matrix4 Translation(float x, float y, float z);
	static Matrix4 Rotation(const Vector3& rotation);
	//static Matrix4 Rotation(const Quaternion& rotation);
	static Matrix4 Rotation(float x, float y, float z);
	static Matrix4 RotationX(float angle);
	static Matrix4 RotationY(float angle);
	static Matrix4 RotationZ(float angle);

	static Matrix4 Scale(const Vector3& scale);
	static Matrix4 Scale(float x, float y, float z);
	static Matrix4 LookAt(const Vector3& position, const Vector3& right, const Vector3& up, const Vector3& forward);
	static Matrix4 LookAt(const Vector3& position, const Vector3& target, const Vector3& up);
	static Matrix4 Orthographic(float width, float height, float zNear, float zFar);
	static Matrix4 Perspective(float fov, float width, float height, float zNear, float zFar);
	static Matrix4 Transpose(const Matrix4& target);

	float& Get(const uint32 row, uint32 col);
	float* GetM();

	Matrix4& operator=(const Matrix4& other);
	Matrix4 operator*(const Matrix4& other);
	Matrix4 operator*=(const Matrix4& other);

	Vector3 operator*(const Vector3& other);

	static const unsigned int elementSize = 4 * 4;

private:
	float elements[elementSize];
};