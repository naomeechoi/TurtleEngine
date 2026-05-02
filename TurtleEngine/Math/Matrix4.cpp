#include "PrecompiledHeader.h"
#include "Matrix4.h"
#include "MathDefine.h"

Matrix4::Matrix4()
{
	memset(elements, 0u, sizeof(float) * elementSize);
}

Matrix4::Matrix4(const Matrix4& other)
{
	memcpy(elements, other.elements, sizeof(float) * elementSize);
}

Matrix4::~Matrix4()
{
}

Matrix4 Matrix4::Identity()
{
	Matrix4 identity;
	identity.Get(0, 0) = 1.0f;  identity.Get(0, 1) = 0.0f;  identity.Get(0, 2) = 0.0f;  identity.Get(0, 3) = 0.0f;
	identity.Get(1, 0) = 0.0f;  identity.Get(1, 1) = 1.0f;  identity.Get(1, 2) = 0.0f;  identity.Get(1, 3) = 0.0f;
	identity.Get(2, 0) = 0.0f;  identity.Get(2, 1) = 0.0f;  identity.Get(2, 2) = 1.0f;  identity.Get(2, 3) = 0.0f;
	identity.Get(3, 0) = 0.0f;  identity.Get(3, 1) = 0.0f;  identity.Get(3, 2) = 0.0f;  identity.Get(3, 3) = 1.0f;

	return identity;
}

Matrix4 Matrix4::Translation(const Vector3& position)
{
	return Matrix4::Translation(position.x, position.y, position.z);
}

Matrix4 Matrix4::Translation(float x, float y, float z)
{
	Matrix4 result;
	result.Get(0, 0) = 1.0f;  result.Get(0, 1) = 0.0f;  result.Get(0, 2) = 0.0f;  result.Get(0, 3) = 0.0f;
	result.Get(1, 0) = 0.0f;  result.Get(1, 1) = 1.0f;  result.Get(1, 2) = 0.0f;  result.Get(1, 3) = 0.0f;
	result.Get(2, 0) = 0.0f;  result.Get(2, 1) = 0.0f;  result.Get(2, 2) = 1.0f;  result.Get(2, 3) = 0.0f;
	result.Get(3, 0) = x;	  result.Get(3, 1) = y;		result.Get(3, 2) = z;     result.Get(3, 3) = 1.0f;

	return result;
}

Matrix4 Matrix4::Rotation(const Vector3& rotation)
{
	return Matrix4::Rotation(rotation.x, rotation.y, rotation.z);
}

/*
Matrix4 Matrix4::Rotation(const Quaternion& rotation)
{
	return Matrix4();
}
*/

Matrix4 Matrix4::Rotation(float x, float y, float z)
{
	return RotationX(x) * RotationY(y) * RotationZ(z);
}

Matrix4 Matrix4::RotationX(float angle)
{
	Matrix4 rx;

	angle *= Math::Deg2Rad;

	float cosX = std::cosf(angle);
	float sinX = std::sinf(angle);

	rx.Get(0, 0) = 1.0f;  rx.Get(0, 1) = 0.0f;  rx.Get(0, 2) = 0.0f;   rx.Get(0, 3) = 0.0f;
	rx.Get(1, 0) = 0.0f;  rx.Get(1, 1) = cosX;  rx.Get(1, 2) = sinX;  rx.Get(1, 3) = 0.0f;
	rx.Get(2, 0) = 0.0f;  rx.Get(2, 1) = -sinX;  rx.Get(2, 2) = cosX;   rx.Get(2, 3) = 0.0f;
	rx.Get(3, 0) = 0.0f;  rx.Get(3, 1) = 0.0f;  rx.Get(3, 2) = 0.0f;   rx.Get(3, 3) = 1.0f;

	return rx;
}

Matrix4 Matrix4::RotationY(float angle)
{
	Matrix4 ry;

	angle *= Math::Deg2Rad;

	float cosY = std::cosf(angle);
	float sinY = std::sinf(angle);

	ry.Get(0, 0) = cosY;	ry.Get(0, 1) = 0.0f;  ry.Get(0, 2) = -sinY;	 ry.Get(0, 3) = 0.0f;
	ry.Get(1, 0) = 0.0f;	ry.Get(1, 1) = 1.0f;  ry.Get(1, 2) = 0.0f;   ry.Get(1, 3) = 0.0f;
	ry.Get(2, 0) = sinY;	ry.Get(2, 1) = 0.0f;  ry.Get(2, 2) = cosY;   ry.Get(2, 3) = 0.0f;
	ry.Get(3, 0) = 0.0f;	ry.Get(3, 1) = 0.0f;  ry.Get(3, 2) = 0.0f;   ry.Get(3, 3) = 1.0f;

	return ry;
}

Matrix4 Matrix4::RotationZ(float angle)
{
	Matrix4 rz;

	angle *= Math::Deg2Rad;

	float cosZ = std::cosf(angle);
	float sinZ = std::sinf(angle);

	rz.Get(0, 0) = cosZ;  rz.Get(0, 1) = sinZ;  rz.Get(0, 2) = 0.0f;  rz.Get(0, 3) = 0.0f;
	rz.Get(1, 0) = -sinZ;  rz.Get(1, 1) = cosZ;   rz.Get(1, 2) = 0.0f;  rz.Get(1, 3) = 0.0f;
	rz.Get(2, 0) = 0.0f;  rz.Get(2, 1) = 0.0f;   rz.Get(2, 2) = 1.0f;  rz.Get(2, 3) = 0.0f;
	rz.Get(3, 0) = 0.0f;  rz.Get(3, 1) = 0.0f;   rz.Get(3, 2) = 0.0f;  rz.Get(3, 3) = 1.0f;

	return rz;
}

Matrix4 Matrix4::Scale(const Vector3& scale)
{
	return Matrix4::Scale(scale.x, scale.y, scale.z);
}

Matrix4 Matrix4::Scale(float x, float y, float z)
{
	Matrix4 result;
	result.Get(0, 0) = x;     result.Get(0, 1) = 0.0f;  result.Get(0, 2) = 0.0f;  result.Get(0, 3) = 0.0f;
	result.Get(1, 0) = 0.0f;  result.Get(1, 1) = y;     result.Get(1, 2) = 0.0f;  result.Get(1, 3) = 0.0f;
	result.Get(2, 0) = 0.0f;  result.Get(2, 1) = 0.0f;  result.Get(2, 2) = z;     result.Get(2, 3) = 0.0f;
	result.Get(3, 0) = 0.0f;  result.Get(3, 1) = 0.0f;  result.Get(3, 2) = 0.0f;  result.Get(3, 3) = 1.0f;

	return result;
}

Matrix4 Matrix4::LookAt(const Vector3& position, const Vector3& right, const Vector3& up, const Vector3& forward)
{
	float x = right.Dot(position);
	float y = up.Dot(position);
	float z = forward.Dot(position);

	Matrix4 result;
	result.Get(0, 0) = right.x;	    result.Get(0, 1) = up.x;	    result.Get(0, 2) = forward.x;	result.Get(0, 3) = 0.0f;
	result.Get(1, 0) = right.y;	    result.Get(1, 1) = up.y;	    result.Get(1, 2) = forward.y;	result.Get(1, 3) = 0.0f;
	result.Get(2, 0) = right.z;		result.Get(2, 1) = up.z;		result.Get(2, 2) = forward.z;	result.Get(2, 3) = 0.0f;
	result.Get(3, 0) = -x;			result.Get(3, 1) = -y;			result.Get(3, 2) = -z;			result.Get(3, 3) = 1.0f;

	return result;
}

Matrix4 Matrix4::LookAt(const Vector3& position, const Vector3& target, const Vector3& up)
{
	Vector3 forward = (target - position).Normalized();
	Vector3 right = up.Cross(forward).Normalized();
	Vector3 upDir = forward.Cross(right).Normalized();

	float x = right.Dot(position);
	float y = upDir.Dot(position);
	float z = forward.Dot(position);

	Matrix4 result;
	result.Get(0, 0) = right.x;	    result.Get(0, 1) = upDir.x;	    result.Get(0, 2) = forward.x;	result.Get(0, 3) = 0.0f;
	result.Get(1, 0) = right.y;	    result.Get(1, 1) = upDir.y;	    result.Get(1, 2) = forward.y;	result.Get(1, 3) = 0.0f;
	result.Get(2, 0) = right.z;		result.Get(2, 1) = upDir.z;		result.Get(2, 2) = forward.z;	result.Get(2, 3) = 0.0f;
	result.Get(3, 0) = -x;			result.Get(3, 1) = -y;			result.Get(3, 2) = -z;			result.Get(3, 3) = 1.0f;

	return result;
}

Matrix4 Matrix4::Orthographic(float width, float height, float zNear, float zFar)
{
	return Matrix4();
}

Matrix4 Matrix4::Perspective(float fov, float width, float height, float zNear, float zFar)
{
	return Matrix4();
}

Matrix4 Matrix4::Transpose(const Matrix4& target)
{
	Matrix4 result = target;

	std::swap(result.Get(0, 1), result.Get(1, 0));
	std::swap(result.Get(0, 2), result.Get(2, 0));
	std::swap(result.Get(0, 3), result.Get(3, 0));

	std::swap(result.Get(1, 2), result.Get(2, 1));
	std::swap(result.Get(1, 3), result.Get(3, 1));
	std::swap(result.Get(2, 3), result.Get(3, 2));

	return result;
}

float& Matrix4::Get(const uint32 row, uint32 col)
{
#if _DEBUG
	assert(row <= 3 && col <= 3);
#endif
	return elements[row + (col * 4)];
}

float* Matrix4::GetM()
{
	return elements;
}

Matrix4& Matrix4::operator=(const Matrix4& other)
{
	if (this == &other)
	{
		return *this;
	}

	memcpy(elements, other.elements, sizeof(float) * elementSize);
	return *this;
}

Matrix4 Matrix4::operator*(const Matrix4& other)
{
	Matrix4 result;
	for (int ix = 0; ix < 4; ++ix)
	{
		result.Get(ix, 0) =
			Get(ix, 0) * other.elements[0 + 0 * 4] +
			Get(ix, 1) * other.elements[1 + 0 * 4] +
			Get(ix, 2) * other.elements[2 + 0 * 4] +
			Get(ix, 3) * other.elements[3 + 0 * 4];

		result.Get(ix, 1) =
			Get(ix, 0) * other.elements[0 + 1 * 4] +
			Get(ix, 1) * other.elements[1 + 1 * 4] +
			Get(ix, 2) * other.elements[2 + 1 * 4] +
			Get(ix, 3) * other.elements[3 + 1 * 4];

		result.Get(ix, 2) =
			Get(ix, 0) * other.elements[0 + 2 * 4] +
			Get(ix, 1) * other.elements[1 + 2 * 4] +
			Get(ix, 2) * other.elements[2 + 2 * 4] +
			Get(ix, 3) * other.elements[3 + 2 * 4];

		result.Get(ix, 3) =
			Get(ix, 0) * other.elements[0 + 3 * 4] +
			Get(ix, 1) * other.elements[1 + 3 * 4] +
			Get(ix, 2) * other.elements[2 + 3 * 4] +
			Get(ix, 3) * other.elements[3 + 3 * 4];
	}

	return result;
}

Matrix4 Matrix4::operator*=(const Matrix4& other)
{
	*this = *this * other;
	return *this;
}

Vector3 Matrix4::operator*(const Vector3& other)
{
	Vector3 result;
	result.x = elements[0] * other.x + elements[4] * other.y + elements[8] * other.z;
	result.y = elements[1] * other.x + elements[5] * other.y + elements[9] * other.z;
	result.z = elements[2] * other.x + elements[6] * other.y + elements[10] * other.z;

	return result;
}
